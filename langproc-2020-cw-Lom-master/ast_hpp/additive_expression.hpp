#ifndef additive_expression_hpp
#define additive_expression_hpp


#include "expression.hpp"

#include <iostream>
#include <string>

class additive_expression
    : public expression
{
private:
    expression* left;
    expression* right;
    std::string op;
public:
    additive_expression(expression* left_, std::string op_, expression* right_);

    virtual ~additive_expression();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

};

#endif