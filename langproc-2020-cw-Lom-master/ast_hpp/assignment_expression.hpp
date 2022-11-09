#ifndef assignment_expression_hpp
#define assignment_expression_hpp


#include "expression.hpp"
#include "Identifier.hpp"

#include <iostream>
#include <string>

class assignment_expression
    : public expression 
{
private:
    expression* left;
    expression* right;
    std::string op;
public:
    assignment_expression(expression* left_, std::string op_, expression* right_);

    virtual ~assignment_expression();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

    std::string get_id_name() const;

    double get_expr_const() const;
};

#endif