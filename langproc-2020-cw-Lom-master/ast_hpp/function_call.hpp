#ifndef function_call_hpp
#define function_call_hpp


#include "expression.hpp"
#include "Scope.hpp"
#include "Identifier.hpp"
#include "argument_list.hpp"


#include <iostream>
#include <string>


class function_call
    : public expression
{
private:
    Identifier* id;
    argument_list* arg_list;
    
public:
    function_call(Identifier* id_,argument_list* arg_list_);

    virtual ~function_call();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

    
};


#endif