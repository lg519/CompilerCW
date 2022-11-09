#ifndef list_hpp
#define list_hpp

#include "node.hpp"


#include <iostream>


class list
    : public node
{

public:
 
    virtual ~list();

    virtual void print(std::ostream &dst) const =0;

    virtual int get_mem_size() const =0;

    virtual void compile(std::ostream &dst) const =0;


};

#endif