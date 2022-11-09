#include "../ast_hpp/ast.hpp"



unary_expression::unary_expression(std::string op_, expression* expr_)
: op(op_)
, expr(expr_)
{
    inc_front = true;
    //std::cout << "CONSTUCTOR OF UNARY EXPR CALLED" << std::endl;
}

unary_expression::unary_expression(std::string op_, expression* expr_, bool inc_front_ )
: op(op_)
, expr(expr_)
,inc_front(inc_front_)
{
    //std::cout << "CONSTUCTOR OF UNARY EXPR CALLED" << std::endl;
}

unary_expression::~unary_expression()
{
    delete expr;
}

void unary_expression::print(std::ostream &dst) const 
{    
    if(this->brackets == true){dst << "(";}

    dst <<op;
    expr->print(dst);

    if(this->brackets == true){dst << ")";}
}

void unary_expression::compile(std::ostream &dst) const 
{
    expr->compile(dst);

    // pop
    dst << "lw      $8,0($sp)" << std::endl;
    dst << "addiu    $sp,$sp,4" << std::endl;

    if(op=="+"){
        //resolve
        dst << "add    $10,$0,$8" << std::endl;
    }

    if(op=="-"){
        //resolve
        dst << "sub    $10,$0,$8" << std::endl;
    }

    if(op=="~"){
        //resolve           
        dst << "nor    $10,$8,$0" << std::endl;

    }

    if(op=="!"){
        //resolve
        dst << "sltiu  $10,$8,1" << std::endl;
        //andi with 0x00ff on godbolt
    }

    if(op == "++" && inc_front==true){
        //assuming we have ++x
        std::string id_name = dynamic_cast<Identifier*>(expr)->get_name();
        int fp_offset = scopeptr->get_fp_offset(id_name);

        //add 1 to $8 and put it in $10
        dst << "addiu    $10,$8,1" << std::endl;
        //modify x in memory
        if(fp_offset == -1)
        {
            //variable is GLOBAL
            //assign
              dst << "sw      $10,"<<id_name<< std::endl;
        }
        else
        {
            //variable is LOCAL
            //assign
            dst << "sw    $10," << fp_offset << "($fp)" << std::endl;
        }
    }

    if(op == "++" && inc_front==false){
        //assuming we have ++x
        std::string id_name = dynamic_cast<Identifier*>(expr)->get_name();
        int fp_offset = scopeptr->get_fp_offset(id_name);

        //$8 and put it in $10
        dst << "move    $10,$8" << std::endl;

        //add 1 to $8 and put it in $8
        dst << "addiu    $8,$8,1" << std::endl;
        //modify x in memory
        if(fp_offset == -1)
        {
            //variable is GLOBAL
            //assign
              dst << "sw      $8,"<<id_name<< std::endl;
        }
        else
        {
            //variable is LOCAL
            //assign
            dst << "sw    $8," << fp_offset << "($fp)" << std::endl;
        }


    }

    if(op == "--" && inc_front==true){
        //assuming we have ++x
        std::string id_name = dynamic_cast<Identifier*>(expr)->get_name();
        int fp_offset = scopeptr->get_fp_offset(id_name);

        //add 1 to $8 and put it in $10
        dst << "addiu    $10,$8,-1" << std::endl;
        //modify x in memory
        if(fp_offset == -1)
        {
            //variable is GLOBAL
            //assign
              dst << "sw      $10,"<<id_name<< std::endl;
        }
        else
        {
            //variable is LOCAL
            //assign
            dst << "sw    $10," << fp_offset << "($fp)" << std::endl;
        }
    }

    if(op == "--" && inc_front==false){
        //assuming we have ++x
        std::string id_name = dynamic_cast<Identifier*>(expr)->get_name();
        int fp_offset = scopeptr->get_fp_offset(id_name);

        //$8 and put it in $10
        dst << "move    $10,$8" << std::endl;

        //add 1 to $8 and put it in $8
        dst << "addiu    $8,$8,-1" << std::endl;
        //modify x in memory
        if(fp_offset == -1)
        {
            //variable is GLOBAL
            //assign
              dst << "sw      $8,"<<id_name<< std::endl;
        }
        else
        {
            //variable is LOCAL
            //assign
            dst << "sw    $8," << fp_offset << "($fp)" << std::endl;
        }


    }

    //push
    dst << "addiu    $sp,$sp,-4" << std::endl;
    dst << "sw       $10,0($sp)" << std::endl;        
    
}


void unary_expression::update_scope(Scope* scope_) 
{
    scopeptr = scope_;
    expr->update_scope(scopeptr);
}

