#ifndef argument_list_hpp
#define argument_list_hpp


#include "list.hpp"
#include "expression.hpp"
#include "Scope.hpp"

#include <iostream>
#include <vector>


class argument_list
    : public list
{

private:
std::vector<expression*> args_vector;

Scope* scopeptr;

public:
    argument_list(expression* decl);
    
    virtual ~argument_list();

    virtual void print(std::ostream &dst) const override;

    int get_mem_size() const override;

    virtual void compile(std::ostream &dst) const override;

    void add_expr(expression* id_);
    
    int get_vector_size();

    void update_scope(Scope* scope_) ;


};

#endif