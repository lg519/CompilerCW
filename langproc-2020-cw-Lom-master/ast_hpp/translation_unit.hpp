#ifndef translation_unit_hpp
#define translation_unit_hpp

#include "node.hpp"

#include <iostream>
#include <vector>


class translation_unit 
    : public node
{
private:
    std::vector<node*> node_list;

public:
    
    translation_unit(node* _node);
    

    virtual ~translation_unit();

    void add_node(node* _node);

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;
};

#endif