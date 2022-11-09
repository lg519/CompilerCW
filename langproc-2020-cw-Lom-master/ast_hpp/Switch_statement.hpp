#ifndef Switch_statement_hpp
#define Switch_statement_hpp

#include "selection_statement.hpp"

#include "expression.hpp"
#include "statement.hpp"
#include "Case_statement.hpp"

#include "Scope.hpp"


#include <iostream>
#include <vector>


class Switch_statement
    : public statement
{

private:
    expression* expr;
    //Switch
    statement* stat;
    std::vector<Case_statement*> case_vector;
public:
    Switch_statement(expression * expr_, statement* stat_ );
    
    virtual ~Switch_statement();

    virtual void print(std::ostream &dst) const override;

    virtual int get_mem_size() const override ;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

    void pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const;


};

#endif