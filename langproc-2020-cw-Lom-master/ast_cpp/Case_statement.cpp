#include "../ast_hpp/ast.hpp"
    
Case_statement::Case_statement(expression* expr_ , statement* stat_,bool default_case_)
: stat(stat_)
, expr(expr_)
, default_case(default_case_)
{}

Case_statement::Case_statement(statement* stat_, bool default_case_)
: stat(stat_)
, default_case(default_case_)
, expr(NULL)
{}

Case_statement::~Case_statement()
{}

void Case_statement::print(std::ostream &dst) const
{
    expr->print(dst);
}

int Case_statement::get_mem_size() const
{
    return 0;
}



void Case_statement::compile(std::ostream &dst) const
{
    dst << case_name << ":" << std::endl;
    
    stat->compile(dst);
    


}

void Case_statement::compile_body(std::ostream &dst,std::string L_Case,std::string L_Body) 
{
    
    //scopeptr->update_break_label(L_Body);
    if (default_case==false)
    {
        expr->compile(dst);
        // pop
        dst << "lw      $9,0($sp)" << std::endl;
        dst << "addiu    $sp,$sp,4" << std::endl;
        

        case_name = L_Case;
        dst << "beq    $24,$9, "<< case_name <<std::endl;
        dst << "nop "<<std::endl;
    }
    else
    {
        case_name = L_Case;
        dst << "b             " << case_name <<std::endl; 
        dst << "nop "<<std::endl;
    }
    
    
}

void Case_statement::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    if (default_case==false)
    {
        expr->update_scope(scope_);
    } 
    stat->update_scope(scope_);
}

expression* Case_statement::get_expr()
{
    return expr;
}

void Case_statement::set_case_name(std::string case_name_)
{
    case_name = case_name_;
}

std::string Case_statement::get_case_name()
{
    return case_name;
}

void Case_statement::pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const
{
    if(dynamic_cast<Return*>(stat)) dynamic_cast<Return*>(stat)->update_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
}