
#include <string>
#include <map>
#include <array>
#include <set>
#include <deque>
#include <cctype>
#include "Exceptions.h"

class Parser{
    public:
    std::deque <std::string> parameters;

    Parser(std::deque<std::string> parameters = std::deque<std::string>());
    Parser(const Parser& other);
    ~Parser() = default;
};

void removeSpaces(std::string& str);
void splitParentheses(std::string& graph_name, std::string& file_name);

bool isCommand(std::string str);
bool isLegalGraphName(std::string str);
bool isLegalParentheses(std::string str);
bool isLegalFileName(std::string file_name);

std::string firstLegalParentheses(std::string& str);
std::string getNextArgument(std::string& str);

std::deque<std::string> subDeque(std::deque<std::string>& total ,std::string par);
std::deque<std::string> stringToDeque(std::string str);