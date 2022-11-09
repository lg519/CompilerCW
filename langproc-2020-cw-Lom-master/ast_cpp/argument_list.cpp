#include "../ast_hpp/ast.hpp"
#include <cassert>


argument_list::argument_list(expression* expr_)
{
    args_vector.push_back(expr_);

}

argument_list::~argument_list()
{
    for (unsigned i = 0; i < args_vector.size(); i++)
    {
        assert(args_vector[i] != NULL);
        delete args_vector[i] ;
    }

}

void argument_list::print(std::ostream &dst) const
{   
    for (unsigned i = 0; i < args_vector.size(); i++)
    {
        args_vector[i]->print(dst);
        dst << ", ";
    }
    
}

extern int max_args_size;

void argument_list::compile(std::ostream &dst) const
{
    int rel_offset = 0;
    for (unsigned i = 0; i < args_vector.size(); i++)
    {   

        //get i-th argument
        args_vector[i]->compile(dst);
        // pop
        dst << "lw      $8,0($sp)" << std::endl;
        dst << "addiu    $sp,$sp,4" << std::endl;

        assert(rel_offset <= max_args_size);
        if(i < 4)
        {   
            //store in ARGUMENT REGISTER
            dst << "move    $" << std::to_string(i+4) << ",$8"<<   std::endl;
        }      
        //store in memory
        dst << "sw      $8," << rel_offset <<"($fp)" << std::endl;
        rel_offset+=4;
        
    }
    
}

void argument_list::add_expr(expression* expr_)
{
    assert(expr_!= NULL);
    
    if(expr_ != NULL)
    {
        args_vector.push_back(expr_);
        
    }
}

int argument_list::get_vector_size()
{
    return args_vector.size();
}

void argument_list::update_scope(Scope* scope_) 
{
    scopeptr = scope_;
    
    for (unsigned i = 0; i < args_vector.size(); i++)
    {
        args_vector[i]->update_scope(scopeptr);
    }
       
}


int argument_list::get_mem_size() const
{
    return 0;
}

