#include "../ast_hpp/ast.hpp"
#include<cassert>
#include<iostream>



compound_statement::compound_statement()
{   
    decl_list = NULL;
    stat_list = NULL;
    scopeptr = new Scope();
}

compound_statement::compound_statement(declaration_list* list_)
{
    decl_list = list_;
    stat_list = NULL;
    scopeptr = new Scope();
}

compound_statement::compound_statement(statement_list* list_)
{
    decl_list = NULL;
    stat_list= list_;
    scopeptr = new Scope();
}

compound_statement::compound_statement(declaration_list* list1_, statement_list* list2_)
{
    decl_list = list1_;
    stat_list = list2_;
    scopeptr = new Scope();
}

compound_statement::~compound_statement()
{
    if(decl_list!=NULL){
        delete decl_list;        
    }
    
    if(stat_list!=NULL){
        delete stat_list;        
    }

    assert(scopeptr!= NULL);
    delete scopeptr;
}

void compound_statement::print(std::ostream &dst) const
{
    
    dst <<"\n";
    dst <<"{";
    dst <<"\n";

    if(decl_list!=NULL){
        decl_list->print(dst);
    }

    if(stat_list!=NULL){
        stat_list->print(dst);
    }
    
    

    
    dst <<"}";
    dst <<"\n";
    
}

int compound_statement::get_mem_size() const
{
    int mem_size = 0;
    if(decl_list!=NULL) mem_size += decl_list->get_mem_size();
    if(stat_list!=NULL) mem_size += stat_list->get_mem_size();
    return mem_size;
}

void compound_statement::compile(std::ostream &dst) const
{
    
    if(decl_list!=NULL){
        decl_list->compile(dst);
    }

    if(stat_list!=NULL){
        stat_list->compile(dst);
    }
    
        
}


void compound_statement::update_local_scope() const
{
    if(decl_list != NULL){
        decl_list->update_scope(scopeptr);
    }
    if(stat_list != NULL){
        stat_list->update_scope(scopeptr);
    }

    
}

void compound_statement::update_scope(Scope* parent_scope_)
{ 
    scopeptr->update_parent_scope(parent_scope_);
}

Scope* compound_statement::get_scope_pointer()
{
    return scopeptr;
}

void compound_statement::pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const
{
    if(stat_list != NULL) stat_list->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame, stack_frame_size);
}

void compound_statement::set_only_case_statements_true(){
    stat_list->set_only_case_statements_true();
}