#ifndef While_statement_hpp
#define While_statement_hpp

#include "iteration_statement.hpp"

#include "expression.hpp"
#include "statement.hpp"

#include "Scope.hpp"


#include <iostream>


class While_statement
    : public iteration_statement
{

private:
    expression* expr;
    //WHILE BODY
    statement* stat_1;
    
    bool do_while;

public:
    While_statement(expression * expr_, statement* stat_1_ );

    While_statement(expression * expr_, statement* stat_1_, bool do_while_);
    
    virtual ~While_statement();

    virtual void print(std::ostream &dst) const override;

    virtual int get_mem_size() const override ;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

    void pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const;


};

#endif
