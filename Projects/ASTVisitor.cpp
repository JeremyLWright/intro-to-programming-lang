#include "ASTVisitor.hpp"
#include <vector>

/* Percent Expression */
int PercentExpression::Execute()
{
    return 0;  
}

PercentExpression::~PercentExpression()
{
}

/* At Expression */
int AtExpression::Execute()
{
    return -1;
}

AtExpression::~AtExpression()
{
}

/* AmpersandExpression */
AmpersandExpression::~AmpersandExpression()
{
}


int AmpersandExpression::Execute()
{
    return 0;
}

/* Comparison */
Comparison::~Comparison()
{
}

int Comparison::Execute()
{
    return 0;
}
