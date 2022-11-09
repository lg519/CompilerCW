#ifndef and_expression_hpp
#define and_expression_hpp


#include "expression.hpp"

#include <iostream>
#include <string>

class and_expression
    : public expression
{
private:
    expression* left;
    expression* right;
    std::string op;
public:
    and_expression(expression* left_, std::string op_, expression* right_);

    virtual ~and_expression();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;
};

#endif