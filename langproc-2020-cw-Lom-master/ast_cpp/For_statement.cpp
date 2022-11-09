#include "../ast_hpp/ast.hpp"

/*For_statement::For_statement(expression_statement* stat_1_, expression_statement* stat_2_,statement* body_)
: stat_1(stat_1_)
, stat_2(stat_2_)
, body(body_)
{}*/

For_statement::For_statement(expression_statement* stat_1_, expression_statement* stat_2_,expression* expr_,statement* body_)
: stat_1(stat_1_)
, stat_2(stat_2_)
, expr(expr_)
, body(body_)
{}


For_statement::~For_statement()
{
    if(stat_1 != NULL) delete stat_1;
    if(stat_2 != NULL) delete stat_2;
    if(expr != NULL) delete expr;
    if(body != NULL) delete body;
    
}

void For_statement::print(std::ostream &dst) const
{
    dst << "for( ";
    stat_1->print(dst);
    dst << ";";
    stat_2->print(dst);

    if (expr != NULL)
    {
        dst << ";";
        expr->print(dst);
    }

    dst << ")" << std::endl;
    body->print(dst);


}

int For_statement::get_mem_size() const
{
    int mem_size = 0;

    mem_size += stat_1->get_mem_size();
    mem_size += stat_2->get_mem_size();
    mem_size += body->get_mem_size();

    return mem_size;
}


static int makeNameUnq=0;

static std::string makeForName()
{
    return "L_for_"+std::to_string(makeNameUnq++);
}

static std::string makeBodyName()
{
    return "L_bodyafterfor_"+std::to_string(makeNameUnq++);
}

void For_statement::compile(std::ostream &dst) const
{
    std::string L_For = makeForName();
    std::string L_Body = makeBodyName();

    if(dynamic_cast<compound_statement*>(body)) dynamic_cast<compound_statement*>(body)->get_scope_pointer()->update_start_label(L_For);
    if(dynamic_cast<compound_statement*>(body)) dynamic_cast<compound_statement*>(body)->get_scope_pointer()->update_break_label(L_Body);

    //declaration statement
    stat_1->compile(dst);
    dst << L_For << ":" << std::endl;
    //evaluate condition each loop
    stat_2->compile(dst);
    // pop condition
    dst << "lw      $8,0($sp)" << std::endl;
    dst << "addiu    $sp,$sp,4" << std::endl;
    //recheck if condition is false
    dst << "beq     $8,$0,"<< L_Body << std::endl;
    dst << "nop            "<<std::endl;
    //for loop body
    body->compile(dst);
    //update statement each loop
    expr->compile(dst);
    dst << "b     "<< L_For << std::endl;
    dst << "nop            "<<std::endl;
    //rest of program body
    dst << L_Body << ":" << std::endl;
 
}

void For_statement::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    
    body->update_scope(scopeptr);
    
    stat_1->update_scope(scopeptr);
    stat_2->update_scope(scopeptr);
    expr->update_scope(scopeptr); 
    
}

void For_statement::pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const
{
    if(dynamic_cast<compound_statement*>(stat_1)) dynamic_cast<compound_statement*>(stat_1)->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
    if(dynamic_cast<Return*>(stat_1)) dynamic_cast<Return*>(stat_1)->update_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
}