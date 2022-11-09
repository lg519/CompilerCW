#include "../ast_hpp/ast.hpp"
#include<cassert>

Break::Break()
{}

Break::~Break()
{}

void Break::print(std::ostream &dst) const
{
    //dst << "Break print" << std::endl;
    dst << "break;" << std::endl;

}

int Break::get_mem_size() const 
{
    return 0;
}

void Break::compile(std::ostream &dst) const 
{
    std::string Break_label = scopeptr->get_break_label();
    dst << "#STARTOFBREAK"<< std::endl;
    dst << "b      "<< Break_label << std::endl;
    dst << "nop           "<< std::endl;

}

void Break::update_scope(Scope* scope_) 
{
    scopeptr = scope_;
}

