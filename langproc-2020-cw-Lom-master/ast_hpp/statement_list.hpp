#ifndef statement_list_hpp
#define statement_list_hpp

#include "list.hpp"
#include "Scope.hpp"
#include "statement.hpp"

#include <iostream>
#include <vector>


class statement_list
    : public list
{

private:
std::vector<statement*> statements_vector;
bool only_case_statements;

Scope* scopeptr;

public:
    statement_list(statement* stat);
    
    virtual ~statement_list();

    virtual void print(std::ostream &dst) const override;

    int get_mem_size() const;

    virtual void compile(std::ostream &dst) const override;

    void add_statement(statement* _statement);

    int get_vector_size();

    void update_scope(Scope* scope_);
        
    void pass_epilogue_information(int fp_position_in_stack_frame,int ra_position_in_stack_frame, int stack_frame_size ) const;

    void set_only_case_statements_true();
    


};

#endif


