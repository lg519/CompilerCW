#include "../ast_hpp/ast.hpp"
#include <cassert>


function_call::function_call(Identifier* id_,argument_list* arg_list_)
: id(id_)
, arg_list(arg_list_)
{}

function_call::~function_call()
{
    if(id!=NULL) delete id;
    if(arg_list!=NULL) delete arg_list;
}

void function_call::print(std::ostream &dst) const
{
    //dst << "function_call print" << std::endl;
    dst << id->get_name() ;
    dst <<"(";
    if(arg_list!= NULL) arg_list->print(dst);
    dst <<")";
    
}


//global variable for arguments
int max_args_size = 100;

void function_call::compile(std::ostream &dst) const
{
    //place args in args section
    if(arg_list!= NULL) arg_list->compile(dst);

    dst << ".option pic0" << std::endl;
    dst << "jal    "<< id->get_name() << std::endl;
    dst << "nop" << std::endl;
    dst << std::endl;
    dst << ".option pic2" << std::endl;

    //push return result on top of the stack for use within expressions
    dst << "addiu    $sp,$sp,-4" << std::endl;
    dst << "sw       $2,0($sp)" << std::endl;
}


void function_call::update_scope(Scope* scope_)
{
    scopeptr = scope_; 
    id->update_scope(scopeptr);
    if(arg_list!=NULL) arg_list->update_scope(scopeptr);  
}




