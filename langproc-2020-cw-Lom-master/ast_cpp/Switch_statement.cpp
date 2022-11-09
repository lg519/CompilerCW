#include "../ast_hpp/ast.hpp"

Switch_statement::Switch_statement(expression * expr_, statement* stat_)
: expr(expr_)
, stat(stat_)
{}

Switch_statement::~Switch_statement()
{
    if(expr != NULL) delete expr;
    if(stat != NULL) delete stat;
}

void Switch_statement::print(std::ostream &dst) const
{
    dst << "Switch( ";
    expr->print(dst);
    dst << " )";
    stat->print(dst);


}

int Switch_statement::get_mem_size() const
{
    return stat->get_mem_size();

}


static int makeNameUnq=0;

static std::string makeCaseName()
{
    return "L_case_"+std::to_string(makeNameUnq++);
}

static std::string makeBodyName()
{
    return "L_endofcasebody_"+std::to_string(makeNameUnq++);
}

static std::string makeStartName()
{
    return "L_switchstart_"+std::to_string(makeNameUnq++);
}

void Switch_statement::compile(std::ostream &dst) const
{
    dynamic_cast<compound_statement*>(stat)->set_only_case_statements_true();
    std::string L_Start = makeStartName();
    
    if(dynamic_cast<compound_statement*>(stat)) dynamic_cast<compound_statement*>(stat)->get_scope_pointer()->update_start_label(L_Start);
    

    
    expr->compile(dst);
    // pop
    dst << "lw      $24,0($sp)" << std::endl;
    dst << "addiu    $sp,$sp,4" << std::endl;
    stat->compile(dst);

}

void Switch_statement::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    expr->update_scope(scopeptr);
    stat->update_scope(scopeptr);
    
}

void Switch_statement::pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const
{
    if(dynamic_cast<compound_statement*>(stat)) dynamic_cast<compound_statement*>(stat)->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
    if(dynamic_cast<Case_statement*>(stat)) dynamic_cast<Case_statement*>(stat)->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
    if(dynamic_cast<Return*>(stat)) dynamic_cast<Return*>(stat)->update_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
}