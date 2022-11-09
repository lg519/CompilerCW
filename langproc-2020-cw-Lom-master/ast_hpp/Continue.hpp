#ifndef Continue_hpp
#define Continue_hpp

#include "expression.hpp"

#include "jump_statement.hpp"
#include "Scope.hpp"


#include <iostream>


class Continue
    : public jump_statement
{

private:
    expression* expr;
    int fp_position_in_stack_frame;
    int ra_position_in_stack_frame;
    int stack_frame_size;
public:
    Continue();
    
    virtual ~Continue();

    virtual void print(std::ostream &dst) const override;

    virtual int get_mem_size() const override ;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

    void update_epilogue_information(int fp_position_in_stack_frame_,int ra_position_in_stack_frame_,int stack_frame_size_);
};

#endif