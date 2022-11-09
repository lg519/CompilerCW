#include "../ast_hpp/ast.hpp"

/*

Enumerator_list::Enumerator_list(Enumerator* enum_)
{enum_vector.push_back(enum_);}



Enumerator_list::~Enumerator_list()
{
    for (unsigned i = 0; i < enum_vector.size(); i++)
    {
        assert(enum_vector[i] != NULL);
        delete enum_vector[i] ;
    }
}

void Enumerator::print(std::ostream &dst) const
{
    //dst << "Array print" << std::endl;
    id->print(dst);
    dst<<"[";
    if(expr) expr->print(dst);
    dst<<"]";
}

void Enumerator::compile(std::ostream &dst) const
{
    //needs implementation
    //dst << "IDENTIFIER SCOPE IS "<< scopeptr << std::endl;
    //gets variable value
    
    std::string name = id->get_name();
    int fp_offset = scopeptr->get_fp_offset(name);
    int old_fp = scopeptr->get_old_fp();
    if(fp_offset == -1)
    {
        //variable is GLOBAL
        dst << "lw      $10,"<<name<< std::endl;
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

std::string Enumerator::get_name()
{
    return id->get_name();
}


void Enumerator::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    id->update_scope(scopeptr);
    expr->update_scope(scopeptr);
    //scopeptr->update_symbol_table(name);    
}

int Enumerator::get_constant() const
{
    return dynamic_cast<Constant*>(expr)->get_value();
}


void Enumerator::compile_expr_brackets(std::ostream &dst) const
{
    expr->compile(dst);
}*/