#include "../ast_hpp/ast.hpp"


Type_Specifier::Type_Specifier(std::string _Type)
: Type(_Type)
{}

Type_Specifier::~Type_Specifier()
{}

void Type_Specifier::print(std::ostream &dst) const 
{
    //dst << "type specifier print" << std::endl;
    dst << Type;
    
}

void Type_Specifier::compile(std::ostream &dst) const 
{
    //needs implementation
}

std::string Type_Specifier::get_type()
{
    return Type;
}




