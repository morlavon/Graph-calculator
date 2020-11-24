#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_


#include <stdexcept>

class Exception : public std::exception{
};

class GraphException :public Exception{
};

class GpointerException :public Exception{
};
/*----------------------------------------------------------------------------------
Gcalc exceptions
----------------------------------------------------------------------------------*/

class NullPointerAccess : public GpointerException{
    public:
    const char* what() const noexcept override{
        return "Error: you are trying to access a null ointer";
    }
};

class IllegalArgument : public Exception{
    public:
    const char* what() const noexcept override{
        return "Error: An Illegal Argument";
    }
};

class IllegalNumberOfArguments : public Exception{
    public:
    const char* what() const noexcept override{
        return "Error: An Illegal number of Arguments";
    }
};

class IllegalParentheses : public Exception{
    public:
    const char* what() const noexcept override{
        return "Error: An Illegal parentheses";
    }
};

class IllegalSymbol : public Exception{
    public:
    const char* what() const noexcept override{
        return "Error: An Illegal symbol";
    }
};

class DeleteNumberOfArguments : public Exception{
    public:
    const char* what() const noexcept override{
        return "Error: to many argumets for delete function";
    }
};

class DeleteNotExist : public Exception{
    public:
    const char* what() const noexcept override{
        return "Error: the graph you are trying to delete does not exist";
    }
};

class PrintNumberOfArguments : public Exception{
    public:
    const char* what() const noexcept override{
        return "Error: to many argumets for print function";
    }
};
/*----------------------------------------------------------------------------------
Graph exceptions
----------------------------------------------------------------------------------*/
class IllegalVertex : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: An Illegal vertex";
    }
};

class IllegalEdge : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: An Illegal edge";
    }
};

class SelfEdge : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: An edge cannot be from a vertex to itself";
    }
};

class RepeatedEdge : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: The same edge declared twice";
    }
};

class RepeatedVertex : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: The same vertex declared twice";
    }
};

class UndefinedVariable : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: An undefined variable " ;
    }
};

class NothingInParentheses : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: nothing inside parentheses" ;
    }
};

class IllegalFileName : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: Illegal file name" ;
    }
};

class IllegalGraphName : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: Illegal Graph name" ;
    }
};

class IllegalFunctionCall : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: Illegal Function call" ;
    }
};

class IllegalFile : public GraphException{
    public:
    const char* what() const noexcept override{
        return "Error: Attempted to load an illegal file" ;
    }
};

#endif