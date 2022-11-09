#ifndef code_block_hpp
#define code_block_hpp

#include "node.hpp"

#include <iostream>
#include"Scope.hpp"

class code_block
    : public node
{
protected:
    Scope* scopeptr;
public:
    virtual ~code_block();

    virtual void print(std::ostream &dst) const =0;

    virtual int get_mem_size() const =0;
    
    virtual void compile(std::ostream &dst) const =0;
};

#endif