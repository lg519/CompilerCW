#include "../ast_hpp/ast.hpp"



Identifier::Identifier(std::string _name)
: name(_name)
//, scopeptr(NULL)
{}

Identifier::~Identifier()
{}

void Identifier::print(std::ostream &dst) const
{
    //dst << "identifier print" << std::endl;
    dst << name;
}

void Identifier::compile(std::ostream &dst) const
{
    //needs implementation
    //gets variable value
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
        dst << "lw      $10,"<< fp_offset <<"($fp)" << std::endl;
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

std::string Identifier::get_name()
{
    return name;
}


void Identifier::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    //scopeptr->update_symbol_table(name);    
}




