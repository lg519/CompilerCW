#include "../ast_hpp/ast.hpp"
#include <cassert>


declaration_list::declaration_list(declaration* decl)
{
    declarations_vector.push_back(decl);

}

declaration_list::~declaration_list()
{
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {
        assert(declarations_vector[i] != NULL);
        delete declarations_vector[i] ;
    }

}

void declaration_list::print(std::ostream &dst) const
{
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {
        declarations_vector[i]->print(dst);
    }
    
}

int declaration_list::get_mem_size() const 
{
    int mem_size=0;
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {

        mem_size += declarations_vector[i]->get_mem_size();

    }
    //local data storage memory padding
    while(mem_size%8!=0) mem_size += 4;
    assert(mem_size%8 == 0);
    return mem_size;
}

void declaration_list::compile(std::ostream &dst) const
{
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {
        declarations_vector[i]->compile(dst);
    }
    
}

void declaration_list::add_declaration(declaration* _declaration)
{
    assert(_declaration!= NULL);
    
    if(_declaration != NULL)
    {
        declarations_vector.push_back(_declaration);
    }
}

int declaration_list::get_vector_size()
{
    return declarations_vector.size();
}

void declaration_list::update_scope(Scope* scope_) 
{
    scopeptr = scope_;
    
    for (unsigned i = 0; i < declarations_vector.size(); i++)
    {
        declarations_vector[i]->update_scope(scopeptr);
    }
    
    
}




