#include <iostream>
#include <stdlib.h>
#include "ast_parser.h"

using namespace std;
namespace {
int callDepth = 0; //Global callDepth, its bad, but at least its in an anonymous namespace.
}

void NumberTerminal:: Print()
{
    PrintIndentation(callDepth);
    cout << currentValue << endl;
}

int NumberTerminal::Execute()
{
    return currentValue;
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

void AtExpression:: Print()
{
    PrintIndentation(callDepth);
    callDepth++;
    cout << "@" << endl;
    left->Print();
    right->Print();
    callDepth--;
}

int AtExpression::Execute()
{
    int left_value, right_value;

    left_value  = left->Execute();
    right_value = right->Execute();

    currentValue = (left_value+5) % right_value;
    return (currentValue);
}


void PercentExpression::Print()
{
    PrintIndentation(callDepth);
    callDepth++;
    cout << "%" << endl;
    exp->Print();
    callDepth--;
}

int PercentExpression::Execute()
{
    int const expValue = exp->Execute();
    int const a = 5*expValue;
    int const b = 3*expValue+10;

    currentValue = max(b, a);
    return currentValue;
}

void Statement::Print()
{
    exp->Print();
}

void Statement::Execute()
{
    int result = exp->Execute();
    cout << "result: " << result << endl;
}

