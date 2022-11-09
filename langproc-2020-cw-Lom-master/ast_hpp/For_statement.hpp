#ifndef For_statement_hpp
#define For_statement_hpp

#include "iteration_statement.hpp"

#include "expression.hpp"
#include "statement.hpp"
#include "expression_statement.hpp"

#include "Scope.hpp"


#include <iostream>


class For_statement
    : public iteration_statement
{

private:
    expression_statement* stat_1;
    expression_statement* stat_2;
    expression* expr;
    statement* body;


public:
    For_statement(expression_statement* stat_1_, expression_statement* stat_2_,statement* body_);

    For_statement(expression_statement* stat_1_, expression_statement* stat_2_,expression* expr_,statement* body_);
    
    virtual ~For_statement();

    virtual void print(std::ostream &dst) const override;

    virtual int get_mem_size() const override ;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

    void pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const;


};

#endif
