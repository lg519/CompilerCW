#ifndef multiplicative_expression_hpp
#define multiplicative_expression_hpp


#include "expression.hpp"

#include <iostream>
#include <string>

class multiplicative_expression
    : public expression
{
private:
    expression* left;
    expression* right;
    std::string op;
public:
    multiplicative_expression(expression* left_, std::string op_, expression* right_);

    virtual ~multiplicative_expression();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;


};



#endif