#include "../ast_hpp/ast.hpp"
#include<cassert>

translation_unit::translation_unit(node* _node)
{
    node_list.push_back(_node);
}


translation_unit::~translation_unit()
{
    for (unsigned i = 0; i < node_list.size(); i++)
    {
        assert(node_list[i]!=NULL);
        delete node_list[i];
        
    }
}

void translation_unit::add_node(node* _node)
{
    assert(_node != NULL);

    if(_node != NULL){ node_list.push_back(_node);}
}

void translation_unit::print(std::ostream &dst) const 
{
    //dst << "translation unit print" << std::endl;
    for (unsigned i = 0; i < node_list.size(); i++)
    {
        node_list[i]->print(dst);
    }
    
}

void translation_unit::compile(std::ostream &dst) const 
{
    
    //.data
    dst << ".data" <<std::endl;
    //say decl is global and compile it
    // compile global declarataions using global decl compile method
    for (unsigned i = 0; i < node_list.size(); i++)
    {
        if(dynamic_cast<declaration*>(node_list[i])) dynamic_cast<declaration*>(node_list[i])->global_compile(dst);
    }

    //dst <<std::endl<<std::endl;
    dst << ".text" <<std::endl;
    //.globl
    //say function is global and compile it
    for (unsigned i = 0; i < node_list.size(); i++)
    {
        if(dynamic_cast<function*>(node_list[i])) 
        {
            //dst<<std::endl;
            dynamic_cast<function*>(node_list[i])->compile(dst);
        }
    }
}

