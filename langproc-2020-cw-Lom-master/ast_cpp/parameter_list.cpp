#include "../ast_hpp/ast.hpp"
#include <cassert>


parameter_list::parameter_list(declaration* decl)
{
    declarations_vector.push_back(decl);

}

parameter_list::~parameter_list()
{
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {
        assert(declarations_vector[i] != NULL);
        delete declarations_vector[i] ;
    }

}

void parameter_list::print(std::ostream &dst) const
{
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {
        declarations_vector[i]->print(dst);
        dst << ", ";
    }
    
}

int parameter_list::get_mem_size() const 
{
    int mem_size=0;
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {

        mem_size += declarations_vector[i]->get_mem_size();

    }

    //Local Data Storage padding
//    while(mem_size%8!=0){
//        mem_size += 4;
//    }
//    return mem_size;
}

void parameter_list::compile(std::ostream &dst) const
{
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {
        declarations_vector[i]->compile(dst);
    }
    
}

void parameter_list::add_declaration(declaration* _declaration)
{
    assert(_declaration!= NULL);
    
    if(_declaration != NULL)
    {
        declarations_vector.push_back(_declaration);
    }
}

int parameter_list::get_vector_size()
{
    return declarations_vector.size();
}

extern int max_args_size;

void parameter_list::update_scope(Scope* scope_, int fp_position_in_stack_frame) 
{
    scopeptr = scope_;
    scopeptr->update_old_fp(fp_position_in_stack_frame);
    int rel_offset = 1;
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {
        //assert(rel_offset - stack_frame_size <= max_args_size);
        declarations_vector[i]->update_scope_param(scopeptr, rel_offset);
        rel_offset+=4;
    }
    
    
}




