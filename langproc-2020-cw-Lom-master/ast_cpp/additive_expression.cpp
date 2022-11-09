#include "../ast_hpp/ast.hpp"
#include<iostream>


additive_expression::additive_expression(expression* left_, std::string op_, expression* right_)
: left(left_)
, op(op_)
, right(right_)
{
    //std::cout << "CONSTUCTOR OF ADDITIVE EXPR CALLED" << std::endl;
}

 additive_expression::~additive_expression()
{
    delete left;
    delete right;
}

void additive_expression::print(std::ostream &dst) const 
{
    if(this->brackets == true){dst << "(";}
    //dst<<"additive print called"<< std::endl;
    left->print(dst);
    dst <<" "<<op<<" ";
    right->print(dst);
    if(this->brackets == true){dst << ")";}
}

void additive_expression::compile(std::ostream &dst) const 
{
    left->compile(dst);
    right->compile(dst);

    // pop
    dst << "lw      $8,0($sp)" << std::endl;
    dst << "addiu    $sp,$sp,4" << std::endl;
    // pop
    dst << "lw      $9,0($sp)" << std::endl;
    dst << "addiu    $sp,$sp,4" << std::endl;
    
    if(op=="+"){
        //resolve
        dst << "add    $10,$9,$8" << std::endl;
    }
    else if(op=="-"){
        //resolve
        dst << "sub      $10,$9,$8" << std::endl;
    }
    else
    {
        std::cerr << "unrecognised op" <<std::endl;
    }
    
    //push
    dst << "addiu    $sp,$sp,-4" << std::endl;
    dst << "sw       $10,0($sp)" << std::endl;
}

void additive_expression::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    left->update_scope(scopeptr);
    right->update_scope(scopeptr);
}


