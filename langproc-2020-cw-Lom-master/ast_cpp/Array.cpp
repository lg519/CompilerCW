#include "../ast_hpp/ast.hpp"



Array::Array(Identifier* id_,expression* expr_)
: id(id_)
, expr(expr_)
{}

Array::~Array()
{
    delete id;
    delete expr;
}

void Array::print(std::ostream &dst) const
{
    //dst << "Array print" << std::endl;
    id->print(dst);
    dst<<"[";
    if(expr) expr->print(dst);
    dst<<"]";
}

void Array::compile(std::ostream &dst) const
{
    //needs implementation
    //dst << "IDENTIFIER SCOPE IS "<< scopeptr << std::endl;
    //gets variable value
    
    std::string name = id->get_name();
    int fp_offset = scopeptr->get_fp_offset(name);
    int old_fp = scopeptr->get_old_fp();
    if(fp_offset == -1)
    {
        //compile expr
        expr->compile(dst);
        // pop
        dst << "lw      $8,0($sp)" << std::endl;
        dst << "addiu    $sp,$sp,4" << std::endl;

        //transform in memory offset
        dst << "sll     $8,$8,2" << std::endl;

        //get array offset
        dst << "la      $13,"<<name<< std::endl;
        dst << "addu     $9,$8,$13" <<std::endl;
        

        //variable is GLOBAL
        dst << "lw      $10,0($9)"<< std::endl;
    }
    else if(fp_offset%4 == 0)
    {
        
        //variable is LOCAL
        //compile expr
        expr->compile(dst);
        // pop
        dst << "lw      $8,0($sp)" << std::endl;
        dst << "addiu    $sp,$sp,4" << std::endl;

        //transform in memory offset
        dst << "sll     $8,$8,2" << std::endl;

        //get array offset
        dst << "li      $9," << fp_offset <<std::endl;
        dst << "addu     $9,$8,$9" <<std::endl;

        //get relative offset form fp
        dst << "addu     $9,$9,$fp" <<std::endl;


        dst << "lw      $10,0($9)" << std::endl;
    }
    else if(fp_offset == 1)
    {   
        //variable is an ARGUMENT STORED IN REGISTER
        dst << "move     $10,$4" << std::endl;
    }
    else if(fp_offset == 5)
    {   
        //variable is an ARGUMENT STORED IN REGISTER
        dst << "move     $10,$5" << std::endl;
    }
    else if(fp_offset == 9)
    {   
        //variable is an ARGUMENT STORED IN REGISTER
        dst << "move     $10,$6" << std::endl;
    }
    else if(fp_offset == 13)
    {   
        //variable is an ARGUMENT STORED IN REGISTER
        dst << "move     $10,$7" << std::endl;
    }
    else
    {
        //variable is an ARGUMENT STORED IN MEMORY
        //remove encoding
        fp_offset = fp_offset-1;
        //load old_fp in a register
        dst << "lw      $8,"<< old_fp <<"($fp)" << std::endl;
        //find the arg wrt old_fp
        dst << "addiu   $8,$8,"<< fp_offset << std::endl;
        
        dst << "lw      $10,0($8)" << std::endl;
    }
    
    //push
    dst << "addiu    $sp,$sp,-4" << std::endl;
    dst << "sw       $10,0($sp)" << std::endl;

    
}

std::string Array::get_name()
{
    return id->get_name();
}


void Array::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    id->update_scope(scopeptr);
    expr->update_scope(scopeptr);
    //scopeptr->update_symbol_table(name);    
}

int Array::get_constant() const
{
    return dynamic_cast<Constant*>(expr)->get_value();
}


void Array::compile_expr_brackets(std::ostream &dst) const
{
    expr->compile(dst);
}