#include "../ast_hpp/ast.hpp"

function_id_args::function_id_args(Identifier* id_,parameter_list* parm_list_)
: id(id_)
, parm_list(parm_list_)
{}

function_id_args::~function_id_args()
{
    if(id!= NULL) delete id;
    if(parm_list != NULL) delete parm_list;
}

void function_id_args::print(std::ostream &dst) const
{
    id->print(dst);
    dst << "(";
    if(parm_list != NULL) parm_list->print(dst);
    dst << ")";
}

void function_id_args::compile(std::ostream &dst) const
{
    //NEED TO LOAD VARIABLES AT OLD FP_OFFSET + rel position offset
    //if(parm_list!=NULL){
    //    parm_list->compile(dst);
    //}
}

void function_id_args::update_scope(Scope* scope_, int fp_position_in_stack_frame)
{
    
    scopeptr = scope_;
    if(parm_list != NULL) parm_list->update_scope(scopeptr,fp_position_in_stack_frame);
}

std::string function_id_args::get_name() const
{
    return id->get_name();
}

int function_id_args::get_mem_size() const
{
    //if(parm_list != NULL)
    //{
    //    return parm_list->get_mem_size();
    //}
    //else
    //{
    //    return 0;
    //}
}