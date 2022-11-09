#ifndef Type_Specifier_hpp
#define Type_Specifier_hpp


#include "expression.hpp"

#include <iostream>
#include <string>

class Type_Specifier
    : public expression
{
private:
    std::string Type;
public:
    Type_Specifier(std::string _Type);

    virtual ~Type_Specifier();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    std::string get_type();


};

#endif