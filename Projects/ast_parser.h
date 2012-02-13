#ifndef _EXP
#define _EXP
/**
 * @brief Abstract Syntax Tree evaluator.
 *
 * @par
 * Copyright Jeremy Wright (c) 2012
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

class IExpression {
    public:
        //Interface definiton for printing the AST
        virtual void Print() = 0;
        virtual int Execute() = 0;
    protected:
        int currentValue;
        virtual void PrintIndentation(int depth=0)
        {
            for(int i = 0; i < depth; ++i)
                cout << "   "; //Example files show 3 spaces per indentation.
        }
};

class OperatorExpression : public IExpression {
    public:    
    OperatorExpression(IExpression *L, IExpression *R):
        left(L), right(R){}
    protected:
        IExpression *left;
        IExpression *right;
};

class NumberTerminal : public IExpression {
    public:
        NumberTerminal(int value)
        {
            currentValue = value; ///TODO Understand why this cannot go in an initializer list.
        }
        void Print();
        int Execute();
};

class PercentExpression : public IExpression {
    protected:
        IExpression *exp;
    public:
        PercentExpression(IExpression *L) : 
            exp(L) {}
        void Print();
        int Execute();
};

class AmpersandExpression : public OperatorExpression {
    public:
        AmpersandExpression(IExpression *L, IExpression *R) : 
            OperatorExpression(L,R) { }
        void Print();
        int Execute();
};


class AtExpression : public OperatorExpression {
    public:
    AtExpression(IExpression *L, IExpression *R) : 
        OperatorExpression(L,R){ };
        void Print();
        int Execute();
};

struct IStatement {
        virtual void Print() = 0;
        virtual void Execute() = 0;
};

class Statement : public IStatement {
    protected:
        IExpression *exp;
    public:
        Statement(IExpression *expression) : 
            exp(expression) {}
        void Print();
        void Execute();
};

#endif /* end of include guard: _EXP */
