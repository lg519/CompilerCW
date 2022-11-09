#include "../ast_hpp/ast.hpp"
#include<iostream>

assignment_expression::assignment_expression(expression* left_, std::string op_, expression* right_)
: left(left_)
, op(op_)
, right(right_)
{
    //std::cout << "CONSTUCTOR OF ADDITIVE EXPR CALLED" << std::endl;
}

assignment_expression::~assignment_expression()
{
    delete left;
    delete right;
}

void assignment_expression::print(std::ostream &dst) const
{
    if(this->brackets == true){dst << "(";}
    //dst<<"additive print called"<< std::endl;
    left->print(dst);
    dst <<" "<<op<<" ";
    right->print(dst);
    if(this->brackets == true){dst << ")";}
    dst <<";"<< std::endl;
}

void assignment_expression::compile(std::ostream &dst) const
{
    //left does not need to be compiled as it's just an id or array
    //left->compile(dst);
    
    right->compile(dst);

    // pop
    //dst << "lw      $8,0($sp)" << std::endl;
    //dst << "addiu    $sp,$sp,4" << std::endl;
    
    std::string id_name;
    if(dynamic_cast<Identifier*>(left)) id_name = dynamic_cast<Identifier*>(left)->get_name();
    if(dynamic_cast<Array*>(left)) id_name = dynamic_cast<Array*>(left)->get_name();
    int fp_offset = scopeptr->get_fp_offset(id_name);

    if(op == "=")
    {
        //resolve
        if(fp_offset == -1)
        {
            //variable is GLOBAL
            if(dynamic_cast<Identifier*>(left))
            {   
            // pop result of RHS
                dst << "lw      $8,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;
            //assign
              dst << "sw      $8,"<<id_name<< std::endl;
            }
            if(dynamic_cast<Array*>(left))
            { 
                //compile expr
                dynamic_cast<Array*>(left)->compile_expr_brackets(dst);
                // pop
                dst << "lw      $11,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;

                //transform in memory offset
                dst << "sll     $11,$11,2" << std::endl;

                //$12 = base of array + offset of array element
                dst << "la      $12," << id_name <<std::endl;
                dst << "addu     $12,$11,$12" <<std::endl;

                // pop result of RHS
                dst << "lw      $8,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;
                //assign
                dst << "sw    $8,0($12)" << std::endl;
            }


        }
        else
        {
            //variable is LOCAL
            if(dynamic_cast<Identifier*>(left))
            {   
                // pop result of RHS
                dst << "lw      $8,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;
                //assign
                dst << "sw    $8," << fp_offset << "($fp)" << std::endl;
            } 
            if(dynamic_cast<Array*>(left))
            { 
                //compile expr
                dynamic_cast<Array*>(left)->compile_expr_brackets(dst);
                // pop
                dst << "lw      $11,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;

                //transform in memory offset
                dst << "sll     $11,$11,2" << std::endl;

                //$12 = base of array + offset of array element
                dst << "li      $12," << fp_offset <<std::endl;
                dst << "addu     $12,$11,$12" <<std::endl;

                //get relative offset form fp
                dst << "addu     $12,$12,$fp" <<std::endl;

                // pop result of RHS
                dst << "lw      $8,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;

                //assign
                dst << "sw    $8,0($12)" << std::endl;
            }
        }
        
    }
    else
    {
        //get old value of id
        if(fp_offset == -1)
        {
            //variable is GLOBAL  
            if(dynamic_cast<Identifier*>(left))
            {           
            dst << "lw      $9,"<<id_name<< std::endl;
            }
            if(dynamic_cast<Array*>(left))
            { 
                //compile expr
                dynamic_cast<Array*>(left)->compile_expr_brackets(dst);
                // pop
                dst << "lw      $11,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;

                //transform in memory offset
                dst << "sll     $11,$11,2" << std::endl;

                //$12 = base of array + offset of array element
                dst << "la      $12," << id_name <<std::endl;
                dst << "addu     $12,$11,$12" <<std::endl;


                //load result of array[expr] in $9
                dst << "lw    $9,0($12)" << std::endl;

                // pop result of RHS
                dst << "lw      $8,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;
            }
            
        }
        else
        {
            //variable is LOCAL
            if(dynamic_cast<Identifier*>(left))
            {  
            dst << "lw      $9,"<< fp_offset <<"($fp)" << std::endl;
            }
            if(dynamic_cast<Array*>(left))
            {
                //compile expr
                dynamic_cast<Array*>(left)->compile_expr_brackets(dst);
                // pop
                dst << "lw      $11,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;

                //transform in memory offset
                dst << "sll     $11,$11,2" << std::endl;

                //$12 = base of array + offset of array element
                dst << "li      $12," << fp_offset <<std::endl;
                dst << "addu     $12,$11,$12" <<std::endl;

                //get relative offset form fp
                dst << "addu     $12,$12,$fp" <<std::endl;

                //load result of array[expr] in $9
                dst << "lw    $9,0($12)" << std::endl;

                // pop result of RHS
                dst << "lw      $8,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;              
            }
        }
        
        
        if (op=="*=")
        { 
            //resolve
            dst << "mult    $9,$8" << std::endl;
            dst << "mflo    $10" << std::endl;
        }
        else if(op=="/=")
        {
            //resolve 
            dst << "div    $9,$8" << std::endl;
            dst << "mfhi    $10" << std::endl;
        }
        else if(op=="%=")
        { 
            //resolve 
            dst << "div    $9,$8" << std::endl;
            dst << "mflo    $10" << std::endl;
        }
        else if(op=="+=")
        {
            //resolve 
            dst << "add    $10,$9,$8" << std::endl;
        }
        else if(op=="-=") 
        {
            //resolve
            dst << "sub    $10,$9,$8" << std::endl;
        }
        else if(op=="<<=")
        {
            //resolve 
            dst << "sll    $10,$9,$8" << std::endl;
        }
        else if(">>=")
        {
            //resolve 
            dst << "srl    $10,$9,$8" << std::endl;
        }
            //resolve
        else if ("&=")
        {
            //resolve 
            dst << "and    $10,$9,$8" << std::endl;
        }
        else if ("^=")
        { 
            //resolve
            dst << "xor    $10,$9,$8" << std::endl;
        }
        else if(op =="|=")
        {
            //resolve 
            dst << "or    $10,$9,$8" << std::endl;
        } 
        else
        {
            std::cerr << "unrecognised op" <<std::endl;  
        }
        
        if(fp_offset == -1)
        {
            //variable is GLOBAL
            if(dynamic_cast<Identifier*>(left)){
                //assign
                dst << "sw      $10,"<<id_name<< std::endl;             
            }
            if(dynamic_cast<Array*>(left))
            { 
                //compile expr
                dynamic_cast<Array*>(left)->compile_expr_brackets(dst);
                // pop
                dst << "lw      $11,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;

                //transform in memory offset
                dst << "sll     $11,$11,2" << std::endl;

                //$12 = base of array + offset of array element
                dst << "la      $12," << id_name <<std::endl;
                dst << "addu     $12,$11,$12" <<std::endl;

                //assign
                dst << "sw    $10,0($12)" << std::endl;
            }
            

        }
        else
        {
            //variable is LOCAL
            if(dynamic_cast<Identifier*>(left)){
                //assign
                dst << "sw    $10," << fp_offset << "($fp)" << std::endl;
            }
            if(dynamic_cast<Array*>(left))
            { 
                //compile expr
                dynamic_cast<Array*>(left)->compile_expr_brackets(dst);
                // pop
                dst << "lw      $11,0($sp)" << std::endl;
                dst << "addiu    $sp,$sp,4" << std::endl;

                //transform in memory offset
                dst << "sll     $11,$11,2" << std::endl;

                //$12 = base of array + offset of array element
                dst << "li      $12," << fp_offset <<std::endl;
                dst << "addu     $12,$11,$12" <<std::endl;

                //get relative offset form fp
                dst << "addu     $12,$12,$fp" <<std::endl;

                //assign
                dst << "sw    $10,0($12)" << std::endl;
            }
        }
    }
    
}

void assignment_expression::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    left->update_scope(scopeptr);
    right->update_scope(scopeptr);    
}

 std::string assignment_expression::get_id_name() const
 {
    return dynamic_cast<Identifier*>(left)->get_name();
 }

 double assignment_expression::get_expr_const() const
 {
     //ONLY USE FOR GLOBAL VARIABLES
    return dynamic_cast<Constant*>(right)->get_value();
 }