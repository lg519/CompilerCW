#include "../ast_hpp/ast.hpp"
    
expression_statement::expression_statement(expression* expr_)
: expr(expr_)
{}

expression_statement::~expression_statement()
{}

void expression_statement::print(std::ostream &dst) const
{
    expr->print(dst);
}

int expression_statement::get_mem_size() const
{
    return 0;
}

void expression_statement::compile(std::ostream &dst) const
{
    expr->compile(dst);
}

void expression_statement::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    expr->update_scope(scope_);
}

