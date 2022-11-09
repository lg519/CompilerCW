#include "../ast_hpp/ast.hpp"


logical_and_expression::logical_and_expression(expression* left_, std::string op_, expression* right_)
: left(left_)
, op(op_)
, right(right_)
{
    //std::cout << "CONSTUCTOR OF logical_and EXPR CALLED" << std::endl;
}

logical_and_expression::~logical_and_expression()
{
    delete left;
    delete right;
}

void logical_and_expression::print(std::ostream &dst) const
{
    if(this->brackets == true){dst << "(";}
    //dst<<"logical_and print called"<< std::endl;
    left->print(dst);
    dst <<" "<<op<<" ";
    right->print(dst);
    if(this->brackets == true){dst << ")";}
}

static int makeNameUnq=0;

static std::string makeBodyName()
{
    return "L_body_"+std::to_string(makeNameUnq++);
}

static std::string makeZeroName()
{
    return "L_zero_"+std::to_string(makeNameUnq++);
}

void logical_and_expression::compile(std::ostream &dst) const
{
    left->compile(dst);
    right->compile(dst);

    // pop
    dst << "lw      $8,0($sp)" << std::endl;
    dst << "addiu    $sp,$sp,4" << std::endl;
    // pop
    dst << "lw      $9,0($sp)" << std::endl;
    dst << "addiu    $sp,$sp,4" << std::endl;
    
    if(op=="&&"){
        //resolve
        //check if left is zero

        std::string L_Body = makeBodyName();
        std::string L_Zero = makeZeroName();
        dst << "beq $9, $0," << L_Zero << std::endl;
        dst << "nop      "<< std::endl;

        //check if right is zero
        dst << "beq $8, $0," << L_Zero << std::endl;
        dst << "nop      "<< std::endl;
        //load one if both true
        dst << "li $10, 1"<< std::endl;
        dst << "b  "<< L_Body<< std::endl;
        //load zero if one or both are false
        dst << L_Zero << ":" << std::endl;
        dst << "li $10, 0"<< std::endl;
        dst << "b  "<< L_Body<< std::endl;
        //rest of body
        dst << L_Body << ":" << std::endl;


    }
    else
    {
        std::cerr << "unrecognised op" <<std::endl;
    }
    
    //push
    dst << "addiu    $sp,$sp,-4" << std::endl;
    dst << "sw       $10,0($sp)" << std::endl;
}

void logical_and_expression::update_scope(Scope* scope_)
{
    scopeptr = scope_;
    left->update_scope(scopeptr);
    right->update_scope(scopeptr);
}
