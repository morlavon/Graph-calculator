#include <iostream>
#include "Parser.h"
#include "Graph.h"
#include <fstream>

enum MODE {batch, interactive};

class Gcalc{
    public:
    Parser parser;
    std::map <std::string, Graph> name_map;

    /*----------------------------------------------------------------------
    function declarations
    ----------------------------------------------------------------------*/
    Gcalc(Parser parser = Parser(), std::map <std::string, Graph> name_map = std::map <std::string, Graph>());
    Gcalc(const Gcalc& other);
    ~Gcalc() = default;

    void excecuteCommandLine();
    void excecuteCorrectCommand();
    void quit();
    void who();
    void reset();
    void print();
    void deleteGraph();
    void save();
    
   
};

/*----------------------------------------------------------------------
function declarations
----------------------------------------------------------------------*/


void gcalc(MODE mode);

bool isNameInMap(std::map<std::string, Graph> name_map, std::string name);
Graph getNextGraph(std::deque <std::string>& parameters , std::map<std::string, Graph>& name_map);
Graph curlyToGraph(std::deque <std::string>& parameters);
Graph compute(Graph g1, Graph g2, std::string symbol);
Graph dequeToGraph(std::deque <std::string>& parameters , std::map<std::string, Graph>& name_map);
Graph load(std::deque <std::string>& parameters); 
void writeGraphToFile(Graph g, std::string file_name);
void writeStringToFile(std::string v, std::ofstream& outfile);
Graph readGraphFromFile(std::string file_name);
std::string readStringFromFile(std::ifstream& infile);
