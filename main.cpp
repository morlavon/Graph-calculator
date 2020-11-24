#include "Gcalc.h"
#include "gw.h"


/*----------------------------------------------------------------------
main
----------------------------------------------------------------------*/

int main(int argc, char** argv) {
    /*
    std::set<std::string> v = {"a", "b", "c"};
    std::set<std::string> e = {"a b"};
    std::set<std::string> e2 = {"b c"};
    Graph g1(v, e);
    Graph g2(v, e2);
    Graph g3;
    Graph* g1_ptr = create();
    //char* p1 = "[a;]";
    //char* p2 = "b";
    //disp(g1_ptr);
    //Graph* g2_ptr = &g2;
    //Graph* g3_ptr = &g3;
    //disp(graphCompliment(g1_ptr, g3_ptr));
    //g1_ptr = addVertex(g1_ptr , "a");
    //g1_ptr = addVertex(g1_ptr , "b");
    //g1_ptr = addEdge(g1_ptr ,);
    disp(g1_ptr);
    //g1_ptr = addVertex(g1_ptr , p2);
    //g1_ptr = addEdge(g1_ptr , p1, p2);
    */
    try{
        if(argc == 1){
            gcalc(interactive);
        }
        else if(argc ==3){
            std::streambuf *cinbuf = std::cin.rdbuf();
            std::streambuf *coutbuf = std::cout.rdbuf();
            std::ifstream fin(*(argv+1));
            std::ofstream fout(*(argv+2));
            std::cin.rdbuf(fin.rdbuf());
            std::cout.rdbuf(fout.rdbuf());
            gcalc(batch);
            std::cin.rdbuf(cinbuf);
            std::cout.rdbuf(coutbuf);

            
        }
        else
        {
            std::cerr<<"Error: illegal number of arguments";
        }
        
    }
    catch(Exception& e){
        std::cout<< e.what() << std::endl;
    }
}
    
    


