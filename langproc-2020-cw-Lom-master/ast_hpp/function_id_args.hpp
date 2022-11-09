#ifndef function_id_args_hpp
#define function_id_args_hpp

#include "expression.hpp"
#include "Identifier.hpp"
#include "parameter_list.hpp"


#include <iostream>
#include <string>


class function_id_args
    : public expression
{
protected:
    Identifier* id;
    parameter_list* parm_list;
public:
    function_id_args(Identifier* id_,parameter_list* parm_list_);
    
    virtual ~function_id_args();

    virtual void print(std::ostream &dst) const;
        

    virtual void compile(std::ostream &dst) const;

    virtual void update_scope(Scope* scope_,int fp_position_in_stack_frame);

    std::string get_name() const;

    int get_mem_size() const;
};

#endif