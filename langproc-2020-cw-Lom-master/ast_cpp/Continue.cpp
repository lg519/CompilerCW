#include "../ast_hpp/ast.hpp"
#include<cassert>

Continue::Continue()
{}

Continue::~Continue()
{}

void Continue::print(std::ostream &dst) const
{
    //dst << "Continue print" << std::endl;
    dst << "Continue;" <<std::endl;

}

int Continue::get_mem_size() const 
{
    return 0;
}

void Continue::compile(std::ostream &dst) const 
{   
    std::string Start_label = scopeptr->get_start_label();
    dst << "#CONTINUE" << std::endl;
    dst << "b      "<< Start_label << std::endl;
    dst << "nop           "<< std::endl;
    
}

void Continue::update_scope(Scope* scope_) 
{
    scopeptr = scope_;
}


void Continue::update_epilogue_information(int fp_position_in_stack_frame_,int ra_position_in_stack_frame_,int stack_frame_size_)
{
    fp_position_in_stack_frame = fp_position_in_stack_frame_;
    ra_position_in_stack_frame = ra_position_in_stack_frame_;
    stack_frame_size = stack_frame_size_;
}
