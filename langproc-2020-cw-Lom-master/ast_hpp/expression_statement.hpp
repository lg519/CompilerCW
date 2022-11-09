#ifndef expression_statement_hpp
#define expression_statement_hpp

#include"statement.hpp"
#include"expression.hpp"
#include"Scope.hpp"

#include <iostream>

class expression_statement
    : public statement
{
private:
expression* expr;
Scope* scopeptr;
public:
    
    expression_statement(expression* expr_);

    virtual ~expression_statement();

    virtual void print(std::ostream &dst) const override;

    virtual int get_mem_size() const override;
    
    virtual void compile(std::ostream &dst) const override;

   virtual void update_scope(Scope* scope_) override;


};

#endif