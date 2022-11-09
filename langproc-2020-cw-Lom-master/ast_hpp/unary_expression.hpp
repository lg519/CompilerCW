#ifndef unary_expression_hpp
#define unary_expression_hpp


#include "expression.hpp"

#include <iostream>
#include <string>

class unary_expression
    : public expression
{
private:  
    std::string op;
    expression* expr;
    bool inc_front;
public:
    unary_expression(std::string op_, expression* expr_);

    unary_expression(std::string op_, expression* expr_, bool inc_front_);

    virtual ~unary_expression();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

};

#endif