#include "Parser.h"
#include <iostream>

/*----------------------------------------------------------------------
static arrays and maps for saved words and operators
----------------------------------------------------------------------*/

std::array <std::string, 6> possible_commands = {"print", "delete", "who", "reset", "quit", "save"};
std::array <char, 14> possible_operators = {'^', '<', '>', '!', '=', '*', '+',
 '-', '|', ',', '(', '{', ')', '}'};
std::map <std::string, std::string> closing_parentheses = {{"(", ")"}, {"[", "]"}, {"{", "}"}};

/*----------------------------------------------------------------------
c'tor and cc'tor:
----------------------------------------------------------------------*/

Parser::Parser(std::deque<std::string> parameters) :
parameters(parameters){}

Parser::Parser(const Parser& other): parameters(other.parameters){}
/*----------------------------------------------------------------------
boolean functions
----------------------------------------------------------------------*/

bool isLegalParentheses(std::string str){
    int par_count = 0;
    char par = '(';
    for(char c : str){
        if(c == par){
            par_count++;
        }
        if(c == ')'){
            par_count--;
        }
        if(par_count < 0){
            return false;
        }
    }
    if(par_count == 0){
        return true;
    }
    else{
        return false;
    }
        
}

bool isCommand(std::string str){
    for (std::string command : possible_commands)
    {
        if(str == command){
            return true;
        }
    }
    return false;
}

bool isLegalGraphName(std::string str){
    if(str.compare("load") == 0){
        return false;
    }
    if (isalpha(str[0])){
        for (std::string::iterator it = str.begin(); it != str.end(); ++it)
        {
            if(!isalpha(*it) && !isdigit(*it)){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool isLegalFileName(std::string file_name){
    for(char c : file_name){
        if(c == '(' || c == ')' || c == ','){
            return false;
        }
    }
    return true;
}

/*----------------------------------------------------------------------
std::string functions
----------------------------------------------------------------------*/

void removeSpaces(std::string& str){
    while(!str.empty() && str[0] == ' '){
        str.erase(0,1);
    }
    while(!str.empty() && str[str.size()-1] == ' '){
        str = str.substr(0, str.size()-1);
    }
}

std::string getNextArgument(std::string& str){
    removeSpaces(str);
    int s_location = 0;
    std::string argument = str;
    for(char c : possible_operators){
        if (str[0] == c){
            str.erase(0,1);
            return argument.substr(0,1);
        } 
    }
    int e_location = s_location;
    for (char c : str){
        if(isalpha(c) || isdigit(c) || c == '[' || c == ']' || c == ';'){
            e_location++;
        }
        else break;
    }
    if(e_location!=s_location){
        str = str.substr(e_location, std::string::npos);
        return argument.substr(0, (e_location-s_location));
    }
    else{
        throw IllegalArgument();
    }
}

void splitParentheses(std::string& graph_name, std::string& file_name){
    if(graph_name.find_last_of(',') == graph_name.npos){
        throw IllegalFileName();
    }
    int comma_location = graph_name.find_last_of(',');
    file_name = graph_name.substr(comma_location + 1, std::string::npos);
    removeSpaces(file_name);
    graph_name = graph_name.substr(0, comma_location);
    removeSpaces(graph_name);
}

std::string firstLegalParentheses(std::string& str){
    int par_count = 0;
    int end_loc = 0;
    for(char c : str){
        if(c == '('){
            par_count++;
        }
        if(c ==')'){
            par_count--;
        }
        if(par_count == 0){
            break;
        }
        end_loc++;
    }
    if(par_count != 0){
        throw IllegalParentheses();
    }
    std::string par = str.substr(0, end_loc + 1);
    str = str.substr(end_loc + 1, std::string::npos);
    return par;

}

/*----------------------------------------------------------------------
std::deque functions
----------------------------------------------------------------------*/

std::deque<std::string> stringToDeque(std::string str){
    
    std::string remain = str;
    std::deque <std::string> arguments;
    if(!isLegalParentheses(remain)){
        throw IllegalParentheses();
    }
    while (!remain.empty()){
        arguments.push_back(getNextArgument(remain));
        removeSpaces(remain);
        if(arguments.back().compare("save") == 0 || arguments.back().compare("load") == 0){
            if(remain.empty()){
                throw IllegalFunctionCall();
            }
            if(remain[0] == '('){   
                std::string legal_par = firstLegalParentheses(remain);
                arguments.push_back(legal_par);
            }
        }
        
    }
    return arguments;
}

std::deque<std::string> subDeque(std::deque<std::string>& total ,std::string par){
    int par_count = 1;
    total.pop_front();
    std::deque<std::string> part;
    while(!total.empty() && par_count != 0){
        part.push_back(total.front());
        total.pop_front();
        if(part.back() == par){
            par_count++;
        }
        if(part.back().compare(closing_parentheses[par]) == 0){
            par_count--;
        }
    }
    if(par_count != 0){
        throw IllegalParentheses();
    }
    part.pop_back();
    return part;
}