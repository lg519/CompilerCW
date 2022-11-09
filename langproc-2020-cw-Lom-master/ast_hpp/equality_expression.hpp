#ifndef equality_expression_hpp
#define equality_expression_hpp


#include "expression.hpp"

#include <iostream>
#include <string>

class equality_expression
    : public expression
{
private:
    expression* left;
    expression* right;
    std::string op;
public:
    equality_expression(expression* left_, std::string op_, expression* right_);

    virtual ~equality_expression();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;
};

#endif