#ifndef If_statement_hpp
#define If_statement_hpp

#include "selection_statement.hpp"

#include "expression.hpp"
#include "statement.hpp"

#include "Scope.hpp"


#include <iostream>


class If_statement
    : public selection_statement
{

private:
    expression* expr;
    //IF
    statement* stat_1;
    //ELSE
    statement* stat_2;
public:
    If_statement(expression * expr_, statement* stat_1_ );

    If_statement(expression * expr_, statement* stat_1_,statement* stat_2_ );
    
    virtual ~If_statement();

    virtual void print(std::ostream &dst) const override;

    virtual int get_mem_size() const override ;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

    void pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const;


};

#endif