#ifndef parameter_list_hpp
#define parameter_list_hpp


#include "list.hpp"
#include "declaration.hpp"
#include "Scope.hpp"

#include <iostream>
#include <vector>


class parameter_list
    : public list
{

private:
std::vector<declaration*> declarations_vector;

Scope* scopeptr;

public:
    parameter_list(declaration* decl);
    
    virtual ~parameter_list();

    virtual void print(std::ostream &dst) const override;

    int get_mem_size() const;

    virtual void compile(std::ostream &dst) const override;

    void add_declaration(declaration* _declaration);
    
    int get_vector_size();

    void update_scope(Scope* scope_, int fp_position_in_stack_frame) ;


};

#endif