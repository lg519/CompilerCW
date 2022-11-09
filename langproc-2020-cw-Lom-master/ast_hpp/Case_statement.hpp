#ifndef Case_statement_hpp
#define Case_statement_hpp

#include"statement.hpp"
#include"expression.hpp"
#include"Scope.hpp"

#include <iostream>

class Case_statement
    : public statement
{
private:
expression* expr;
statement* stat;
bool default_case;
Scope* scopeptr;
std::string case_name;
public:
    
    Case_statement(expression* expr_ ,statement* stat_,bool default_case_);

    Case_statement(statement* stat_, bool default_case_);

    virtual ~Case_statement();

    virtual void print(std::ostream &dst) const override;

    virtual int get_mem_size() const override;
    
    virtual void compile(std::ostream &dst) const override;

   virtual void update_scope(Scope* scope_) override;

   expression* get_expr();
   
   void set_case_name(std::string case_name_);

   std::string get_case_name();

   void compile_body(std::ostream &dst,std::string L_Case,std::string L_Body) ;

   void pass_epilogue_information(int fp_position_in_stack_frame, int ra_position_in_stack_frame, int stack_frame_size ) const;
   
};

#endif