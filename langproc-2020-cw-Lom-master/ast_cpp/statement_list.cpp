#include "../ast_hpp/ast.hpp"
#include<cassert>


statement_list::statement_list(statement* stat)
{
    statements_vector.push_back(stat);
    only_case_statements = false;
}

statement_list::~statement_list()
{
    for (unsigned i = 0; i < statements_vector.size(); i++)
    {
        assert(statements_vector[i] != NULL);
        delete statements_vector[i] ;
    }
}

void statement_list::print(std::ostream &dst) const
{
    for (unsigned i = 0; i < statements_vector.size(); i++)
    {
        statements_vector[i]->print(dst);
    }
    
}

int statement_list::get_mem_size() const 
{
    int mem_size=0;
    for (unsigned i = 0; i < statements_vector.size(); i++)
    {

        mem_size += statements_vector[i]->get_mem_size();

    }
    return mem_size;

}

static int makeNameUnq=0;

static std::string makeCaseName()
{
    return "L_case_"+std::to_string(makeNameUnq++);
}

static std::string makeBodyName()
{
    return "L_caseend_"+std::to_string(makeNameUnq++);
}

void statement_list::compile(std::ostream &dst) const
{
    
    std::string L_Body = makeBodyName();
    if(only_case_statements==true) scopeptr->update_break_label(L_Body);
    for (unsigned i = 0; i < statements_vector.size(); i++)
    {
        if (dynamic_cast<Case_statement*>(statements_vector[i])!=NULL)
        {
            std::string L_Case = makeCaseName();
            dynamic_cast<Case_statement*>(statements_vector[i])->compile_body(dst,L_Case,L_Body);
                
        }
        else
        {
            
        }   
        
    }

    for (unsigned i = 0; i < statements_vector.size(); i++)
    {
        if (dynamic_cast<Case_statement*>(statements_vector[i])!=NULL)
        {
        dynamic_cast<Case_statement*>(statements_vector[i])->compile(dst);
        }
        else
        {
            statements_vector[i]->compile(dst);
        }
    }
    if(only_case_statements==true) dst << L_Body << ":" << std::endl;
    
}

void statement_list::add_statement(statement* _statement)
{
    assert(_statement!= NULL);
    
    if(_statement != NULL)
    {
        statements_vector.push_back(_statement);
    }
}

int statement_list::get_vector_size()
{
    return statements_vector.size();
}

void statement_list::update_scope(Scope* scope_) 
{
    scopeptr = scope_;
    
    for (unsigned i = 0; i < statements_vector.size(); i++)
    {
        statements_vector[i]->update_scope(scopeptr);
    }
    
    
}
        
        
void statement_list::pass_epilogue_information(int fp_position_in_stack_frame,int ra_position_in_stack_frame, int stack_frame_size ) const
{
    for (unsigned i = 0; i < statements_vector.size(); i++)
    {
        //need this step for every statement that might have a scope
        if(dynamic_cast<Return*>(statements_vector[i])) dynamic_cast<Return*>(statements_vector[i])->update_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
        if(dynamic_cast<If_statement*>(statements_vector[i])) dynamic_cast<If_statement*>(statements_vector[i])->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
        if(dynamic_cast<While_statement*>(statements_vector[i])) dynamic_cast<While_statement*>(statements_vector[i])->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
        if(dynamic_cast<For_statement*>(statements_vector[i])) dynamic_cast<For_statement*>(statements_vector[i])->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
        if(dynamic_cast<Switch_statement*>(statements_vector[i])) dynamic_cast<Switch_statement*>(statements_vector[i])->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
        if(dynamic_cast<Case_statement*>(statements_vector[i])) dynamic_cast<Case_statement*>(statements_vector[i])->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);


        if(dynamic_cast<compound_statement*>(statements_vector[i])) dynamic_cast<compound_statement*>(statements_vector[i])->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
    }
} 

void statement_list::set_only_case_statements_true(){
    only_case_statements = true;
}







