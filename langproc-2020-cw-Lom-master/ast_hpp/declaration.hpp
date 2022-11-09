#ifndef declaration_hpp
#define declaration_hpp

#include"code_block.hpp"
#include"Type_Specifier.hpp"
#include"expression.hpp"


#include<iostream>

class declaration
    : public code_block
{
private:
    Type_Specifier *type_specifier;
    expression *expr;
    
public:
   
    declaration(Type_Specifier * type_specifier_, expression * expr_ );

    virtual ~declaration();

    virtual void print(std::ostream &dst) const override;

    int get_mem_size() const;

    virtual void compile(std::ostream &dst) const override;

    void update_scope(Scope* scope_);

    void update_scope_param(Scope* scope_, int rel_offset_);

    void global_compile(std::ostream &dst) const;

};

#endif