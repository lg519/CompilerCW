#include "../ast_hpp/ast.hpp"

If_statement::If_statement(expression * expr_, statement* stat_1_)
: expr(expr_)
, stat_1(stat_1_)
, stat_2(NULL)
{}


If_statement::If_statement(expression * expr_, statement* stat_1_, statement* stat_2_)
: expr(expr_)
, stat_1(stat_1_)
, stat_2(stat_2_)
{}

If_statement::~If_statement()
{
    if(expr != NULL) delete expr;
    if(stat_1 != NULL) delete stat_1;
    if(stat_2 != NULL) delete stat_2;
}

void If_statement::print(std::ostream &dst) const
{
    dst << "if( ";
    expr->print(dst);
    dst << " )";
    stat_1->print(dst);

    if(stat_2 != NULL)
    {
    dst << "else{ ";
    stat_2->print(dst);
    dst << " }";
    }

}

int If_statement::get_mem_size() const
{
    // need to change for else part
    if(stat_2 == NULL) return stat_1->get_mem_size();
    else return stat_1->get_mem_size() + stat_2->get_mem_size();

}


static int makeNameUnq=0;

static std::string makeElseName()
{
    return "L_else_"+std::to_string(makeNameUnq++);
}

static std::string makeBodyName()
{
    return "L_bodyafterif_"+std::to_string(makeNameUnq++);
}

void If_statement::compile(std::ostream &dst) const
{
    expr->compile(dst);

    // pop
    dst << "lw      $8,0($sp)" << std::endl;
    dst << "addiu    $sp,$sp,4" << std::endl;

    std::string L_Body = makeBodyName();

    if(stat_2 == NULL)
    {
        
        // branch to Rest of the body
        dst << "beq     $8,$0,"<< L_Body << std::endl;
        dst << "nop     " << std::endl;
        stat_1->compile(dst);
        dst << L_Body << ":" << std::endl;
    }
    else
    {
        std::string L_Else = makeElseName();

        dst << "beq     $8,$0,"<< L_Else << std::endl;
        dst << "nop     " << std::endl;

        stat_1->compile(dst);

        dst << "b   " << L_Body << std::endl;
        dst << "nop     " << std::endl;

        dst << L_Else << ":" << std::endl;
        stat_2->compile(dst);
        dst << L_Body << ":" << std::endl;
    }
}

void If_statement::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    expr->update_scope(scopeptr);
    stat_1->update_scope(scopeptr);
    if (stat_2!=NULL) stat_2->update_scope(scopeptr);
    
}

void If_statement::pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const
{
    if(dynamic_cast<compound_statement*>(stat_1)) dynamic_cast<compound_statement*>(stat_1)->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
    if(dynamic_cast<Return*>(stat_1)) dynamic_cast<Return*>(stat_1)->update_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);

    if(dynamic_cast<compound_statement*>(stat_2)) dynamic_cast<compound_statement*>(stat_2)->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
    if(dynamic_cast<Return*>(stat_2)) dynamic_cast<Return*>(stat_2)->update_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
}