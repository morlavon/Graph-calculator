#include <iostream>
#include "Graph.h"
/*---------------------------------------------------------------------------------
helper functions:
-----------------------------------------------------------------------------------*/
std::string getFrom(std::string e){
    int space_location = e.find_first_of(' ');
    //std::cout<<"from: "+e.substr(0, space_location)<<std::endl;
    return e.substr(0, space_location);
}

std::string getTo(std::string e){
    int space_location = e.find_first_of(' ');
    //std::cout<<"to: "+ e.substr(space_location+1, std::string::npos)<<std::endl;
    return e.substr(space_location+1, std::string::npos);
}

//C'tor
Graph::Graph(const std::set <std::string>& vertices, const std::set <std::string>& edges){
    this->vertices = vertices;
    this->edges = edges;
}

//CC'tor
Graph::Graph(const Graph& other): vertices(other.vertices), edges(other.edges){}

//print function
void Graph::printGraph(){
    for(std::string v : vertices){
        std::cout<< v << std::endl;
    }
    std::cout<< "$" << std::endl;
    for(std::string e : edges){
        std::cout << e << std::endl;
    }
}

/*---------------------------------------------------------------------------------
building functions:
-----------------------------------------------------------------------------------*/
void Graph::addVertex(const std::string v){
    Graph g = *this;
    if(!g.isLegalVertex(v)){
        throw IllegalVertex();
    }
    this->vertices.insert(v);
}

void Graph::removeVertex(const std::string v){
    Graph gcopy(*this);
    for(std::string e : gcopy.edges){
        
        if((getFrom(e).compare(v) == 0) || (getTo(e).compare(v) == 0)){
            this->edges.erase(e);
        }
    }
    this->vertices.erase(v);
}

void Graph::addEdge(const std::string e){
    Graph g = *this;
    if(!g.isLegalEdge(e)){
        throw IllegalEdge();
    }
    this->edges.insert(e);
}

void Graph::removeEdge(const std::string e){
    this->edges.erase(e);
}
/*---------------------------------------------------------------------------------
operator functions:
-----------------------------------------------------------------------------------*/

Graph Graph::operator+(const Graph other){
    Graph gtemp=*this;
    for(std::string v : other.vertices){
        if(gtemp.isLegalVertex(v)){
            gtemp.addVertex(v);
        }
    }
    for(std::string e : other.edges){
        if(gtemp.isLegalEdge(e)){
            gtemp.addEdge(e);
        }
    }
    return gtemp;
}

Graph Graph::operator-(const Graph other)const{
    Graph gtemp=*this;
    for(std::string v : other.vertices){
        gtemp.removeVertex(v);
    }
    for(std::string e : other.edges){
        gtemp.removeEdge(e);
    }
    return gtemp;
}

Graph Graph::operator^(const Graph other){
    Graph g;
    Graph g2 = other;
    for(std::string v : this->vertices){
        if(g2.containsVertex(v)){
            g.addVertex(v);
        }
    }
    for(std::string e : this->edges){
        if(g2.containsEdge(e)){
            g.addEdge(e);
        }
    }
    return g;
}

Graph Graph::operator*(const Graph other){
    Graph gtemp;
    for(std::string v1: this->vertices){
        for(std::string v2 : other.vertices){
            gtemp.addVertex("[" + v1 + ";" + v2 + "]");
            std::cout<< "[" + v1 + ";" + v2 + "]" << " vert"<<std::endl;
        }
    }
    for(std::string e1: this->edges){
        for(std::string e2 : other.edges){
            gtemp.addEdge("[" + getFrom(e1) + ";" + getFrom(e2) + "] " + "[" + getTo(e1) + ";" + getTo(e2) + "]");
            std::cout<<  "[" + getFrom(e1) + ";" + getFrom(e2) + "] " + "[" + getTo(e1) + ";" + getTo(e2) + "]"<< " edge"<<std::endl;
        }
    }
    return gtemp;
}

Graph Graph::operator!(){
    Graph gtemp = *this;
    for(std::string v1 : this->vertices){
        for(std::string v2 : this->vertices){
            if(isLegalEdge(v1 + " " + v2)){
                gtemp.addEdge(v1 + " " + v2);
            }
        }
    }
    for(std::string e1 : this->edges){
        gtemp.removeEdge(e1);
    }
    return gtemp;
}

bool Graph::containsVertex(std::string v){
    for(std::string v1 : this->vertices){
        if (v1.compare(v) == 0){
            return true;
        }
    }
    return false;
}

bool Graph::containsEdge(std::string e){    
    for(std::string e1 : this->edges){
        if (e1.compare(e) == 0){
            return true;
        }
    }
    return false;
}

bool Graph::isLegalVertex(std::string v){
    Graph g = *this;
    if(g.containsVertex(v)){
        return false;
    }
    if(!g.isLegalVertexName(v)){
        return false;
    }
    return true;
}

bool Graph::isLegalVertexName(std::string v){
    int par_count = 0;
    for(char c : v){
        if(!isalpha(c) && !isdigit(c) && c!= '[' && c!= ']' && c!= ';'){
            return false;
        }
        if(c == '['){
            par_count++;
        }
        if(c == ']'){
            par_count--;
        }
        if(par_count<0){
            return false;
        }
        if(par_count == 0 && c ==';'){
            return false;
        }
    }
    if(par_count != 0){
        return false;
    }
    return true;
}

bool Graph::isLegalEdge(std::string e){
    Graph g = *this;
    if(g.containsEdge(e)){
        return false;
    }
    if(!g.isLegalEdgeName(e)){
        return false;
    }
    return true;
}

bool Graph::isLegalEdgeName(std::string e){
    Graph g = *this;
    int space_loc = e.find_first_of(' ');
    std::string v1 = e.substr(0, space_loc);
    std::string v2 = e.substr(space_loc + 1, std::string::npos);
    if(v1.compare(v2) == 0){
        return false;
    }
    if(g.containsVertex(v1) && g.containsVertex(v2)){
        return true;
    }
    else{
        return false;
    }
}



int Graph::verticesSize(){
    return this->vertices.size();
}

int Graph::edgesSize(){
    return this->edges.size();
}