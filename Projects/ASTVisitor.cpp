#include "ASTVisitor.hpp"
#include <vector>
namespace {
    int callDepth = 0;
}

/* Percent Expression */
int PercentExpression::Execute()
{
    int const expValue = exp->Execute();
    int const a = 5*expValue;
    int const b = 3*expValue+10;

    currentValue = max(b, a);
    return currentValue;
}

PercentExpression::~PercentExpression()
{
}

void PercentExpression::Print()
{
    PrintIndentation(callDepth);
    callDepth++;
    cout << "%" << endl;
    exp->Print();
    callDepth--;
}

/* At Expression */
int AtExpression::Execute()
{
     int left_value, right_value;

    left_value  = left->Execute();
    right_value = right->Execute();

    currentValue = (left_value+5) % right_value;
    return (currentValue);
}

AtExpression::~AtExpression()
{
}

void AtExpression:: Print()
{
    PrintIndentation(callDepth);
    callDepth++;
    cout << "@" << endl;
    left->Print();
    right->Print();
    callDepth--;
}

/* AmpersandExpression */
AmpersandExpression::~AmpersandExpression()
{
}


int AmpersandExpression::Execute()
{
     int left_value, right_value;

    left_value  = left->Execute()+2;
    right_value = right->Execute()+3;

    currentValue = left_value + right_value;
    int temp;
    if(left_value<right_value) 
    {
        swap(left_value, right_value);
    }
    while((temp = left_value%right_value) && temp != 0) 
    {
        swap(left_value, right_value);
        right_value = temp;
    }
    currentValue = right_value;

    return (currentValue);
}

void AmpersandExpression:: Print()
{
    PrintIndentation(callDepth);
    cout << "&" << endl;
    callDepth++;
    left->Print();
    right->Print();
    callDepth--;
}


/* Comparison */
Comparison::~Comparison()
{
}

int Comparison::Execute()
{
    int left_value = left->Execute();
    int right_value = right->Execute();
//    cout << "Comparing " << left_value << " to " << right_value;
    bool returnValue = false;
    switch(_compOp)
    {
        case N_EQ:
            left_value != right_value ? returnValue = true : returnValue = false;
            break;
        case IS_EQ:
             left_value == right_value ? returnValue = true : returnValue = false;
            break;
        case LT_EQ:
             left_value <= right_value ? returnValue = true : returnValue = false;
            break;
        case GT_EQ:
             left_value >= right_value ? returnValue = true : returnValue = false;
            break;
        case GT:
             left_value > right_value ? returnValue = true : returnValue = false;
            break;
        case LT:
             left_value < right_value ? returnValue = true : returnValue = false;
            break;
    }

//    cout << "returning " << returnValue;
    return returnValue;

}

void Comparison::Print()
{
    left->Print();
   cout << " " << _compOp << " ";
   right->Print();
}

/* Declarations */


