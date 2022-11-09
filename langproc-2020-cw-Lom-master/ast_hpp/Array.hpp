#ifndef Array_hpp
#define Array_hpp


#include "expression.hpp"
#include "Scope.hpp"
#include "Identifier.hpp"


#include <iostream>
#include <string>


class Array
    : public expression
{
private:
    Identifier* id;
    expression* expr;
    
public:
    Array(Identifier* id_,expression* expr_);

    virtual ~Array();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    std::string get_name();

    virtual void update_scope(Scope* scope_) override;

    int get_constant() const;

    void compile_expr_brackets(std::ostream &dst) const;

    
};

#endif