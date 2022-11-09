#ifndef statement_hpp
#define statement_hpp


#include "code_block.hpp"


#include <iostream>




class statement
    : public code_block
{

    
public:
   
    virtual ~statement();

    virtual void print(std::ostream &dst) const =0;

    virtual int get_mem_size() const =0;
    
    virtual void compile(std::ostream &dst) const =0;

    virtual void update_scope(Scope* scope_) =0;


};

#endif