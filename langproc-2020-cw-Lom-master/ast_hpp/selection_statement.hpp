#ifndef selection_statement_hpp
#define selection_statement_hpp


#include "statement.hpp"


#include <iostream>
#include <string>

class selection_statement
    : public statement
{

public:
   
    virtual ~selection_statement();

    virtual void print(std::ostream &dst) const =0;

    virtual int get_mem_size() const =0;
    
    virtual void compile(std::ostream &dst) const =0;

    virtual void update_scope(Scope* scope_) =0;


};

#endif