#include "Gcalc.h"


/*----------------------------------------------------------------------
c'tor , cc'tor:
----------------------------------------------------------------------*/

Gcalc::Gcalc(Parser parser, std::map <std::string, Graph> name_map) :
parser(parser),
name_map(name_map) 
{}

Gcalc::Gcalc(const Gcalc& other): parser(other.parser), name_map(other.name_map){}

/*----------------------------------------------------------------------
gcalc
----------------------------------------------------------------------*/

void gcalc(MODE mode){
    std::string user_command = "Gcalc";
    Gcalc gcalc;
    do{
        try{
            if(std::cin.eof()){
                break;
            }
            if(mode == interactive){
            std::cout << "Gcalc> ";
            }
            std::getline(std::cin, user_command);
            removeSpaces(user_command);
            gcalc.parser.parameters = stringToDeque(user_command);
            /*
            for (std::string str : gcalc.parser.parameters)
            {
                std::cout<<str<<std::endl;
            }
            */
            gcalc.excecuteCommandLine();
        }
        catch(const Exception& e){
            std::cout << e.what() << '\n';
        }
    } while (user_command.compare("quit") != 0);    
}
/*----------------------------------------------------------------------
command functions
----------------------------------------------------------------------*/
void Gcalc::quit(){
    return;
}

void Gcalc::who(){
    for(auto pair : name_map){
        std::cout<<pair.first<<std::endl;
    }
}

void Gcalc::reset(){
    std::map<std::string, Graph> new_map;
    name_map = new_map;
}

void Gcalc::print(){
    if(parser.parameters.front().compare("(") !=0 || parser.parameters.back().compare(")") !=0){
        throw PrintNumberOfArguments();
    }
    parser.parameters.pop_back();
    parser.parameters.pop_front();
    Graph g = dequeToGraph(parser.parameters, name_map);
    if(!parser.parameters.empty()){
        throw PrintNumberOfArguments();
    }
    g.printGraph();
}

void Gcalc::deleteGraph(){
    if(parser.parameters.front().compare("(") != 0 || parser.parameters.back().compare(")") != 0){
        throw DeleteNotExist();
    }
    parser.parameters.pop_front();
    parser.parameters.pop_back();
    if(parser.parameters.size() != 1){
        throw DeleteNumberOfArguments();
    }
    if(!isNameInMap(name_map, parser.parameters.front())){
        throw DeleteNotExist();
    }
    name_map.erase(parser.parameters.front());
}

void Gcalc::save(){
    if(parser.parameters.size() != 1 || parser.parameters.front().size() <= 3 ){
        throw IllegalParentheses();
    }
    std::string graph_name = parser.parameters.front();
    if(graph_name[0] != '(' || graph_name[graph_name.size() - 1] != ')'){
        throw IllegalFunctionCall();
    }
    graph_name = graph_name.substr(1, graph_name.size() - 2);
    std::string file_name;
    splitParentheses(graph_name, file_name);
    if(!isLegalFileName(file_name)){
        throw IllegalFileName();
    }
    std::deque <std::string> expression = stringToDeque(graph_name);
    Graph g = dequeToGraph(expression, name_map);
    writeGraphToFile(g, file_name);
}

Graph load(std::deque<std::string>& parameters){
    std::string file_name = parameters.front().substr(1, parameters.front().size() - 2);
    removeSpaces(file_name); 
    parameters.pop_front();
    if(!isLegalFileName(file_name)){
        throw IllegalFileName();
    }
    return readGraphFromFile(file_name);
}

/*----------------------------------------------------------------------
boolean functions
----------------------------------------------------------------------*/

bool isNameInMap(std::map<std::string, Graph> name_map, std::string name){
    for(auto pair : name_map){
        if (pair.first.compare(name) == 0){
            return true;
        }
    }
    return false;
}

/*----------------------------------------------------------------------
functions that return graphs:
----------------------------------------------------------------------*/

Graph compute(Graph g1, Graph g2, std::string symbol){
    if(symbol.compare("+") == 0){
        return g1 + g2;
    }
    else if(symbol.compare("-") == 0){
        return g1 - g2;
    }
    else if(symbol.compare("^") == 0){
        return g1 ^ g2;
    }
    else if(symbol.compare("*") == 0){
        return g1 * g2;
    }
    else{
        throw IllegalSymbol();
    }
}

Graph curlyToGraph(std::deque <std::string>& parameters){
    bool comma_turn = false;
    Graph g;
    if(parameters.empty()) {
        return g;
    }
    if(parameters.size() ==1 && parameters.front() == "|"){
        parameters.pop_front();
        return g;
    }
    while(!parameters.empty() && parameters.front() != "|"){
        if(comma_turn == true){
            if(parameters.front().compare(",") != 0){
                throw IllegalVertex();
            }
        }
        else if(g.isLegalVertex(parameters.front())){
            g.addVertex(parameters.front());
        }
        else{
            throw IllegalVertex();
        }
        parameters.pop_front();
        comma_turn = !comma_turn;
    }
    if(comma_turn == false){
        throw IllegalVertex();
    }
    if(parameters.empty()){
        return g;
    }
    if(parameters.front() =="|"){
            parameters.pop_front();
    }
    
    comma_turn =false;
    while(parameters.size() >= 5){
        if(comma_turn == true){
            if(parameters.front().compare(",") != 0){
                throw IllegalEdge();
            }
            else{
                parameters.pop_front();
            }
        } 
        else if((parameters[0].compare("<") == 0) && (g.containsVertex(parameters[1])) &&
        (parameters[2].compare(",") == 0) &&  (g.containsVertex(parameters[3])) && 
        (parameters[4].compare(">") == 0) && g.isLegalEdge(parameters[1] + " " + parameters[3])){
            g.addEdge(parameters[1] + " " + parameters[3]);
            for (int i = 0; i < 5; i++){
                parameters.pop_front();
            }
        }
        else
        {
            throw IllegalEdge();
        }
        comma_turn = !comma_turn;
    }
    if(parameters.size() != 0){
        throw IllegalEdge();
    }
    return g;
}

Graph dequeToGraph(std::deque <std::string>& parameters , std::map<std::string, Graph>& name_map){
    if(parameters.empty()){
        throw IllegalArgument();
    }
    Graph g = getNextGraph(parameters, name_map);
    
    while(!parameters.empty()){
        std::cout << "is calculating"<<std::endl;
        std::string symbol = parameters.front();
        parameters.pop_front();
        Graph g2 = getNextGraph(parameters, name_map);
        g = compute(g, g2, symbol);
    }
    return g;
}

Graph getNextGraph(std::deque <std::string>& parameters , std::map<std::string, Graph>& name_map){
    Graph g;
    if(parameters.empty()){
        throw IllegalArgument();
    }
    if(parameters.front().compare("!") == 0 && parameters.size() > 1){
        parameters.pop_front();
        return !(getNextGraph(parameters, name_map));
    }
    else if(parameters.front().compare("{") == 0){
        std::deque <std::string> part = subDeque(parameters, "{");
        g =  curlyToGraph(part);
    }
    else if(parameters.front().compare("load") == 0){
        parameters.pop_front();
        g = load(parameters);
    }
    else if(isNameInMap(name_map, parameters.front())){
        g = name_map[parameters.front()];
        parameters.pop_front();
    }
    else if(parameters.front().compare("(") == 0){
        std::deque <std::string> part = subDeque(parameters, "(");
        g =  dequeToGraph(part, name_map);
    }
    else{
        throw IllegalArgument();
    }
    return g;
}

/*----------------------------------------------------------------------
excecute functions:
----------------------------------------------------------------------*/

void Gcalc::excecuteCorrectCommand(){
    std::string command = parser.parameters.front();
    parser.parameters.pop_front();
    if(command.compare("who") == 0){
        if(!parser.parameters.empty()){
            throw IllegalFunctionCall();
        }
        this->who();
    }
    else if(command.compare("quit") == 0){
        if(!parser.parameters.empty()){
            throw IllegalFunctionCall();
        }
        this->quit();
    }
    else if(command.compare("reset") == 0){
        if(!parser.parameters.empty()){
            throw IllegalFunctionCall();
        }
        this->reset();
    }
    else if(command.compare("print") == 0){
        this->print();
    }
    else if(command.compare("save") == 0){
        this->save();
    }
    else if(command.compare("delete") == 0){
        this->deleteGraph();
    }
    
    
}

void Gcalc::excecuteCommandLine(){
    if(parser.parameters.empty()){
        return;
    }
    else if(isCommand(parser.parameters.front())){
        this->excecuteCorrectCommand();
    }
    else if(isLegalGraphName(parser.parameters.front()) && parser.parameters[1].compare("=") == 0){
        std::string name = parser.parameters.front();
        parser.parameters.pop_front();
        parser.parameters.pop_front();
        Graph g = dequeToGraph(parser.parameters, name_map);
        if(isNameInMap(name_map, name)){
            name_map.erase(name);
        }
        name_map.insert({name, g});
    }
    else{
        throw IllegalArgument();
    }

}

/*----------------------------------------------------------------------
file functions:
----------------------------------------------------------------------*/
Graph readGraphFromFile(std::string file_name){
    Graph g;
    std::ifstream infile(file_name, std::ios_base::binary);
    if(!infile){
        throw IllegalFile();
    }
    unsigned int num_of_vertices;
    unsigned int num_of_edges;
    infile.read((char*)&num_of_vertices, sizeof(unsigned int));
    infile.read((char*)&num_of_edges, sizeof(unsigned int));
    for(unsigned int i = 0; i < num_of_vertices ; i++){
        std::string v = readStringFromFile(infile);
        if(g.isLegalVertex(v)){
            g.addVertex(v);
        }
        else{
            throw IllegalVertex();
        }
    }
    for(unsigned int i = 0; i < num_of_edges ; i++){
        std::string v1 = readStringFromFile(infile);
        std::string v2 = readStringFromFile(infile);
        std::string e = v1 + " " + v2;
        if(g.isLegalEdge(e)){
            g.addEdge(e);
        }
        else{
            throw IllegalEdge();
        }
    }
    if(infile.peek() != EOF){
        throw IllegalFile();
    }
    return g;
}

void writeGraphToFile(Graph g, std::string file_name){
    std::ofstream outfile(file_name, std::ios_base::binary);
    unsigned int num_vertices = g.verticesSize();
    unsigned int num_edges = g.edgesSize();
    outfile.write((const char*)&num_vertices, sizeof(unsigned int));
    outfile.write((const char*)&num_edges, sizeof(unsigned int));
    for(std::string v : g.vertices){
       writeStringToFile(v, outfile);
    }
    for(std::string e : g.edges){
        std::string v1 = getFrom(e);
        std::string v2 = getTo(e);
        writeStringToFile(v1, outfile);
        writeStringToFile(v2, outfile);
    }
}

void writeStringToFile(std::string v, std::ofstream& outfile){
    unsigned int v_size = v.size();
    outfile.write((const char*)&v_size, sizeof(int));
     for(char c : v){
            outfile.write((const char*)&c, sizeof(char));
        }
}

std::string readStringFromFile(std::ifstream& infile){
    if(infile.peek() == EOF){
        throw IllegalFile();
    }
    int size;
    infile.read((char*)&size, sizeof(unsigned int));
    std::string name;
    for (int i = 0; i < size; i++)
    {
        if(infile.peek() == EOF){
            throw IllegalFile();
        }    
        name+=infile.get();
    }
    return name;
}
