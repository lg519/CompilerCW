#include "../ast_hpp/ast.hpp"
#include<cassert>

Return::Return(expression *_expr)
: expr(_expr)
, fp_position_in_stack_frame(0)
, stack_frame_size(0)
{}

Return::~Return()
{
    assert(expr != NULL);
    delete expr;
}

void Return::print(std::ostream &dst) const
{
    //dst << "return print" << std::endl;
    dst << "return " ;
    
    expr->print(dst);

    dst << ";" ;



}

int Return::get_mem_size() const 
{
    return 0;
}

void Return::compile(std::ostream &dst) const 
{
    //to do later
    expr->compile(dst);
    //pop
    dst << "lw      $8,0($sp)" << std::endl;
    dst << "addiu    $sp,$sp,4" << std::endl;
    //resolve
    dst << "move    $2,$8" << std::endl;

    //EPILOGUE
    dst << std::endl;
    dst << "#EPILOGUE" <<std::endl;
    dst << "move    $sp,$fp" << std::endl;
    dst << "lw      $31," << ra_position_in_stack_frame << "($sp)" << std::endl;
    dst << "lw      $fp," << fp_position_in_stack_frame << "($sp)" << std::endl;
    dst << "addiu   $sp,$sp," << stack_frame_size << std::endl;
    dst << "jr       $31" << std::endl;
    dst << "nop" << std::endl;

}

void Return::update_scope(Scope* scope_) 
{
    scopeptr = scope_;
    expr->update_scope(scopeptr);
}


void Return::update_epilogue_information(int fp_position_in_stack_frame_,int ra_position_in_stack_frame_,int stack_frame_size_)
{
    fp_position_in_stack_frame = fp_position_in_stack_frame_;
    ra_position_in_stack_frame = ra_position_in_stack_frame_;
    stack_frame_size = stack_frame_size_;
}
