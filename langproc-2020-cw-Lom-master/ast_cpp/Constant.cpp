#include "../ast_hpp/ast.hpp"

Constant::Constant(double _value)
: value(_value)
{
    //std::cout << "CONSTUCTOR OF CONST CALLED" << std::endl;
}

Constant::~Constant()
{}

void Constant::print(std::ostream &dst) const 
{
    std::cerr << "const print called" << std::endl;
    //dst << "constant print" << std::endl;
    dst << value;
}

void Constant::compile(std::ostream &dst) const
{      
    //resolve
    dst << "li       $8,"<< value << std::endl;

    //push 
    dst << "addiu    $sp,$sp,-4" << std::endl;
    dst << "sw       $8,0($sp)" << std::endl;
    
}


void Constant::update_scope(Scope* scope_)
{
    scopeptr = scope_;
}

double Constant::get_value() const
{
    return value;
}