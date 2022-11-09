#include "../ast_hpp/ast.hpp"

While_statement::While_statement(expression * expr_, statement* stat_1_)
: expr(expr_)
, stat_1(stat_1_)
, do_while(false)
{}

While_statement::While_statement(expression * expr_, statement* stat_1_, bool do_while_)
: expr(expr_)
, stat_1(stat_1_)
, do_while(do_while_)
{}


While_statement::~While_statement()
{
    if(expr != NULL) delete expr;
    if(stat_1 != NULL) delete stat_1;
}

void While_statement::print(std::ostream &dst) const
{
    dst << "while( ";
    expr->print(dst);
    dst << " )";
    stat_1->print(dst);

}

int While_statement::get_mem_size() const
{
    return stat_1->get_mem_size();
}


static int makeNameUnq=0;

static std::string makeWhileName()
{
    
    
    return "L_while_"+std::to_string(makeNameUnq++);
}

static std::string makeBodyName()
{
    return "L_bodyafterwhile_"+std::to_string(makeNameUnq++);
}

void While_statement::compile(std::ostream &dst) const
{
    
    std::string L_While = makeWhileName();
    if(dynamic_cast<compound_statement*>(stat_1)) dynamic_cast<compound_statement*>(stat_1)->get_scope_pointer()->update_start_label(L_While);
    std::string L_Body = makeBodyName();
    if(dynamic_cast<compound_statement*>(stat_1)) dynamic_cast<compound_statement*>(stat_1)->get_scope_pointer()->update_break_label(L_Body);


    if(do_while == false)
    {
        //WHILE   

        dst << L_While << ":" << std::endl;

        //Evaluate EXPR
        expr->compile(dst);
        // pop
        dst << "lw      $8,0($sp)" << std::endl;
        dst << "addiu    $sp,$sp,4" << std::endl;
        
        //check if EXPR evaluates to FALSE
        dst << "beq     $8,$0,"<< L_Body << std::endl;
        dst << "nop     " << std::endl;

        //execute WHILE BODY
        stat_1->compile(dst);

        
        dst << "b   " << L_While << std::endl;
        dst << "nop     " << std::endl;
        dst << L_Body << ":" << std::endl;


    }
    else
    {
        //DO WHILE


        dst << L_While << ":" << std::endl;
        stat_1->compile(dst);

        //Evaluate EXPR
        expr->compile(dst);
        // pop
        dst << "lw      $8,0($sp)" << std::endl;
        dst << "addiu    $sp,$sp,4" << std::endl;
        
        //check if EXPR evaluates to FALSE
        dst << "beq     $8,$0,"<< L_Body << std::endl;
        dst << "nop     " << std::endl;
        
        dst << "b   " << L_While << std::endl;
        dst << "nop     " << std::endl;
        dst << L_Body << ":" << std::endl;
    }
}

void While_statement::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    expr->update_scope(scopeptr);
    stat_1->update_scope(scopeptr);
    
}

void While_statement::pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const
{
    if(dynamic_cast<compound_statement*>(stat_1)) dynamic_cast<compound_statement*>(stat_1)->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
    if(dynamic_cast<Return*>(stat_1)) dynamic_cast<Return*>(stat_1)->update_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
}