
#ifndef GRAPH_H_
#define GRAPH_H_
#include <string>
#include <set>
#include "Exceptions.h"



class Graph{
    public:
        
    std::set <std::string> vertices = {};
    std::set <std::string> edges = {};
    
    
    explicit Graph(const std::set <std::string>& vertices = std::set<std::string>(), const std::set <std::string>& edges = std::set <std::string>());
    Graph(const Graph& other);
    ~Graph() = default;
    void printGraph();
    void addVertex(const std::string v);
    void removeVertex(const std::string v);
    void addEdge(const std::string e);
    void removeEdge(const std::string e);

    Graph operator -(const Graph other) const;
    Graph operator +(const Graph other);
    Graph operator ^(const Graph other);
    Graph operator *(const Graph other);
    Graph operator !();
    bool isLegalVertex(std::string v);
    bool isLegalEdge(std::string e);
    bool containsVertex(std::string v);
    bool containsEdge(std::string e);
    int verticesSize();
    int edgesSize();

    bool isLegalVertexName(std::string v);
    bool isLegalEdgeName(std::string e);

};
std::string getFrom(std::string e);
std::string getTo(std::string e);

#endif