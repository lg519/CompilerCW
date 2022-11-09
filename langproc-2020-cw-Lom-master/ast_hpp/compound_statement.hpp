#ifndef compound_statement_hpp
#define compound_statement_hpp

#include"code_block.hpp"
#include"declaration_list.hpp"
#include"statement_list.hpp"


#include <iostream>



class compound_statement
    : public statement
{

private:
    declaration_list* decl_list;
    statement_list* stat_list;

    

public:

    compound_statement();

    compound_statement(declaration_list* list_);

    compound_statement(statement_list* list_);

    compound_statement(declaration_list* list1_, statement_list* list2_);
    
    virtual ~compound_statement();

    virtual void print(std::ostream &dst) const override;

    int get_mem_size() const;

    virtual void compile(std::ostream &dst) const override;

    void update_local_scope() const;

    void update_scope(Scope* parent_scope_) override;

    Scope* get_scope_pointer();

    void pass_epilogue_information(int fp_position_in_stack_frame,int ra_position_in_stack_frame, int stack_frame_size ) const;

    void set_only_case_statements_true();
};

#endif