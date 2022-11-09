#ifndef Identifier_hpp
#define Identifier_hpp


#include "expression.hpp"
#include "Scope.hpp"


#include <iostream>
#include <string>


class Identifier
    : public expression
{
private:
    std::string name;
    
public:
    Identifier(std::string _name);

    virtual ~Identifier();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    std::string get_name();

    virtual void update_scope(Scope* scope_) override;

    
};

#endif