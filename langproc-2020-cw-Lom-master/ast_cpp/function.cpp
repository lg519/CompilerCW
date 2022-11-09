#include "../ast_hpp/ast.hpp"
#include<cassert>


   
function::function(Type_Specifier *_type_specifier, function_id_args * _id_args, compound_statement *_compound_statement )
: type_specifier(_type_specifier)
, id_args(_id_args)
, body(_compound_statement)
{}

function::~function()
{
    assert(type_specifier!= NULL);
    delete type_specifier;

    assert(id_args != NULL );
    delete id_args; 
    
    assert(body!= NULL);
    delete body;
    
}

void function::print(std::ostream &dst) const
{

    //dst << "function print" << std::endl;

    type_specifier->print(dst);
    dst << " ";
    id_args->print(dst);
    body->print(dst);
}

extern int max_args_size;

int function::get_stack_frame_size() const
{
    int stack_frame_size = 0;
    stack_frame_size += body->get_mem_size();
    stack_frame_size += max_args_size;

    //allocate space to store $fp and $ra
    stack_frame_size+=8;
    
    //stack frame padding 
    while(stack_frame_size%8!=0) stack_frame_size += 4;

    assert(stack_frame_size%8 == 0);
    return stack_frame_size;
}

void function::compile(std::ostream &dst) const
{
    //might 
    int fp_position_in_stack_frame = (get_stack_frame_size() - 8);
    int ra_position_in_stack_frame = (get_stack_frame_size() - 4);
    int stack_frame_size =  (get_stack_frame_size());

    //Declare it as global
    dst << ".globl "<<id_args->get_name() << std::endl;
    //LABEL
    dst << id_args->get_name() <<":" << std::endl;

    dst << "#PROLOGUE" <<std::endl;
    dst << "addiu   $sp,$sp," << -stack_frame_size << std::endl;   
    dst << "sw      $31," << ra_position_in_stack_frame << "($sp)" << std::endl;
    dst << "sw      $fp," << fp_position_in_stack_frame << "($sp)" << std::endl;
    dst << "move    $fp,$sp"<< std::endl;
    dst <<std::endl;

    //to use parameters
    id_args->update_scope(body->get_scope_pointer(), fp_position_in_stack_frame);
    
    
    body->pass_epilogue_information(fp_position_in_stack_frame,ra_position_in_stack_frame,stack_frame_size);
    body->compile(dst);
    
    

    //std::cout<< "SYMBOL TABLE PRINT "  <<std::endl;
    //body->get_scope_pointer()->print_symbol_table();
    //std::cout<< "END SYMBOL TABLE PRINT " << std::endl;

    //implicit return 0
    //dst << "move    $2,$0" << std::endl;
    //EPILOGUE
    //dst << "move    $sp,$fp" << std::endl;
    //dst << "lw      $fp," << fp_position_in_stack_frame << "($sp)" << std::endl;
    //dst << "addiu   $sp,$sp," << stack_frame_size << std::endl;
    //dst << "jr       $31" << std::endl;
    //dst << "nop" << std::endl;
}




