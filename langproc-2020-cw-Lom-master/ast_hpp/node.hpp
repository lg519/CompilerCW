#ifndef node_hpp
#define node_hpp

#include <iostream>

class node
{

public:
   
    virtual ~node();

    virtual void print(std::ostream &dst) const =0;

    virtual void compile(std::ostream &dst) const =0;


};

#endif