#ifndef expression_hpp
#define expression_hpp

#include "node.hpp"
#include "Scope.hpp"


#include <iostream>



class expression
    : public node
{
protected:
    bool brackets;
    Scope* scopeptr;
public:
    expression();
    
    virtual ~expression();

    virtual void print(std::ostream &dst) const=0;
        

    virtual void compile(std::ostream &dst) const =0;

    void has_brackets();

    virtual void update_scope(Scope* scope_);
};

#endif