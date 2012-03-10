#include "Symbol.h"

Symbol::Ptr Symbol::construct(Identifier id)
{
    Symbol::Ptr c(new Symbol(id));
    c->self = c;
    return c;
}

Symbol::Ptr Symbol::construct(Identifier id, bool isConst)
{
    Symbol::Ptr c(new Symbol(id, isConst));
    c->self = c;
    return c;
}

Symbol::Symbol(Identifier id):
    prop_value(4837), //Default initialization value for Language X
    prop_isConst(false),
    prop_name(id)
{
}

Symbol::Symbol(Identifier id, bool isConst):
    prop_value(4837), //Default initialization value for Language X
    prop_isConst(isConst),
    prop_name(id)
{
}

Symbol::~Symbol()
{
}


Symbol::Identifier Symbol::GetName() const
{
    return prop_name;
}

Symbol::valueType Symbol::GetValue() const
{
    return prop_value;
}

bool Symbol::GetConstness() const
{
    return prop_isConst;
}

void Symbol::SetValue(valueType const value)
{
    prop_value = value;
}

