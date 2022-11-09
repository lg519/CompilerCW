#ifndef function_hpp
#define function_hpp

#include "node.hpp"

#include "compound_statement.hpp"
#include "function_id_args.hpp"
#include "Type_Specifier.hpp"

#include <iostream>



class function
    : public node
{
private:
    Type_Specifier *type_specifier;
    function_id_args *id_args;
    compound_statement *body;
public:
   
    function(Type_Specifier *_type_specifier, function_id_args * _id_args, compound_statement *_compound_statement );

    virtual ~function();

    virtual void print(std::ostream &dst) const override;

    int get_stack_frame_size() const;

    virtual void compile(std::ostream &dst) const override;

};

#endif