#include "../ast_hpp/ast.hpp"


expression::expression()
:brackets(false)
{}

expression::~expression()
{}

void expression::has_brackets()
{
    brackets = true;
}

void expression::update_scope(Scope* scope_)
{
    scopeptr = scope_;
}

