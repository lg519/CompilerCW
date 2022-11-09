#include "../ast_hpp/ast.hpp"
#include<cassert>

   
declaration::declaration(Type_Specifier * type_specifier_, expression *expr_ )
: type_specifier(type_specifier_)
, expr(expr_)
{}

declaration::~declaration()
{
    assert(type_specifier!= NULL);
    delete type_specifier;

    assert(expr != NULL );
    delete expr; 
    
}

void declaration::print(std::ostream &dst) const
{

    //dst << "declaration print" << std::endl;

    type_specifier->print(dst);
    dst << " ";
    if(dynamic_cast<assignment_expression*>(expr)) expr->print(dst);
    else
    {
        expr->print(dst);
        dst << ";" << std::endl;

    }
    
}

int declaration::get_mem_size() const 
{
    if(dynamic_cast<Array*>(expr))
    {
        return dynamic_cast<Array*>(expr)->get_constant()*4;
    }
    else if ((type_specifier->get_type())== "int")
    {
        return 4;
    }
    else if ((type_specifier->get_type())== "double")
    {
        return 8;
    }
    
}

void declaration::compile(std::ostream &dst) const
{
    //dst << "DECLARATION SCOPE IS "<< scopeptr << std::endl;
    if(dynamic_cast<Identifier*>(expr))
    {}
    else if(dynamic_cast<Array*>(expr))
    {}
    else
    {
        //dst << "It's NOT an identifier and it's NOT an Array" << std::endl;
        expr->compile(dst);
    }
}

void declaration::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    expr->update_scope(scopeptr);

    //update symbol table
    if(dynamic_cast<Identifier*>(expr)) scopeptr->update_symbol_table(dynamic_cast<Identifier*>(expr)->get_name());
    if(dynamic_cast<assignment_expression*>(expr)) scopeptr->update_symbol_table(dynamic_cast<assignment_expression*>(expr)->get_id_name()); 
    if(dynamic_cast<Array*>(expr)) scopeptr->update_symbol_table_array(dynamic_cast<Array*>(expr)->get_name(),dynamic_cast<Array*>(expr)->get_constant());
}


void declaration::global_compile(std::ostream &dst) const
{
    std::string name;
    if(dynamic_cast<Identifier*>(expr)) name = dynamic_cast<Identifier*>(expr)->get_name();
    if(dynamic_cast<assignment_expression*>(expr)) name = dynamic_cast<assignment_expression*>(expr)->get_id_name();
    if(dynamic_cast<Array*>(expr)) name = dynamic_cast<Array*>(expr)->get_name();
    if(dynamic_cast<function_id_args*>(expr)) name = dynamic_cast<function_id_args*>(expr)->get_name();
    
    dst <<".globl "<< name << std::endl;

     if(!dynamic_cast<function_id_args*>(expr)) dst <<name<<": "<<".word ";
    if(dynamic_cast<assignment_expression*>(expr)) dst << dynamic_cast<assignment_expression*>(expr)->get_expr_const();
    if(dynamic_cast<Array*>(expr)) dst << "0:" << std::to_string(dynamic_cast<Array*>(expr)->get_constant());
    dst << std::endl;
}


void declaration::update_scope_param(Scope* scope_,int rel_offset_)
{
    scopeptr = scope_;
    expr->update_scope(scopeptr);

    std::string name;
    if(dynamic_cast<Identifier*>(expr)) name = dynamic_cast<Identifier*>(expr)->get_name();

    scopeptr->update_symbol_table_param(name, rel_offset_);

}
