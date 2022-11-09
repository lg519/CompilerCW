#ifndef Constant_hpp
#define Constant_hpp


#include "expression.hpp"

#include <iostream>


class Constant
    : public expression
{
private:
    double value;
public:
    Constant(double _value);
   
    virtual ~Constant();

    virtual void print(std::ostream &dst) const override;

    virtual void compile(std::ostream &dst) const override;

    virtual void update_scope(Scope* scope_) override;

    double get_value() const;
};

#endif