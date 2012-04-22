/**
 * @brief Classes for the Abstract Syntax Tree
 *
 * @par
 * Copyright Jeremy Wright (c) 2012 
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef _ASTVISITOR
#define _ASTVISITOR

#include <iostream>
#include <SymbolTable.h>
#include <sstream>
using namespace std;

extern int yylineno;

struct ASTNode {
    public: 
        virtual string ToString() = 0;
};

struct Program : public ASTNode {
    virtual string ToString()
    {
        return "Program:: ";  
    }
};

struct Block : public ASTNode {
    virtual string ToString()
    {
        return "Block:: ";  
    }
};

struct Declaration : public ASTNode {
    virtual string ToString()
    {
        return "Declaration:: ";  
    }
};

struct VariableDeclaration : public Declaration {
    virtual string ToString()
    {
        return "VariableDeclaration:: ";  
    }
};

struct ConstantDeclaration : public Declaration {
    virtual string ToString()
    {
        return "ConstantDeclaration:: ";  
    }
};

struct Statement : public ASTNode {
    virtual string ToString()
    {
        return "Statement:: ";  
    }
};

struct Expression : public ASTNode {
    virtual string ToString()
    {
        return "Expression:: ";  
    }
    virtual int Execute() = 0;
    Symbol::WeakPtr currentValue;
};

struct Assignment : public Statement {

    Assignment(Expression* rhs):
        _rhs(rhs)
    {
    }

    virtual string ToString()
    {
        return "Assignment:: ";  
    }
    Expression* _rhs;
};

struct PrintStmt : public Statement {
    virtual string ToString()
    {
        return "PrintStmt:: ";  
    }
};
#if 0
struct IfStmt : public Statement {
    virtual string ToString()
    {
        return "IfStmt:: ";  
    }
};

struct DoStmt : public Statement {
    
    virtual string ToString()
    {
        return "DoStmt:: ";  
    }
};

struct Condition : public ASTNode {
    virtual string ToString()
    {
        return "Condition:: ";  
    }
};
#endif
struct PercentExpression : public Expression {
    PercentExpression(Expression *L):
        exp(L) {}
    virtual ~PercentExpression();
    virtual string ToString()
    {
        return "SimpleExpression:: ";  
    }
    int Execute();
    protected:
        Expression *exp;
};

struct OperatorExpression : public Expression {
    OperatorExpression(Expression *L, Expression *R):
        left(L), right(R) {}
    protected:
        Expression *left;
        Expression *right;
};

struct AmpersandExpression : public OperatorExpression {
    AmpersandExpression(Expression *L, Expression* R):
        OperatorExpression(L, R) {}
    virtual ~AmpersandExpression();
    virtual string ToString()
    {
        return "SimpleExpression:: ";  
    }
    int Execute();
};

struct AtExpression : public OperatorExpression {
    AtExpression(Expression *L, Expression* R):
        OperatorExpression(L, R) {}
    virtual ~AtExpression();
    virtual string ToString()
    {
        return "SimpleExpression:: ";  
    }
    int Execute();
};
/*
struct UniTerm : public Expression {
    UniTerm(Expression *L):
        exp(L) {}

    virtual string ToString()
    {
        return "UniTerm:: ";  
    }
};
*/

struct Comparison : public OperatorExpression {
    Comparison(Expression* L, Expression* R, int compOp):
        OperatorExpression(L, R),
        _compOp(compOp)
    {
    }
    virtual ~Comparison();
    int Execute();
    int _compOp;
};

struct Term : public Expression {
    virtual string ToString()
    {
        return "Term:: ";  
    }
};

struct Factor : public Expression {
    Factor(int value):
        _value(value),
        _lineno(yylineno)
    {
    }

    Factor(Symbol::WeakPtr identifier):
        _identifier(identifier),
        _value(-1),
        _lineno(yylineno)
    {
    }

    virtual string ToString()
    {
        stringstream ss;

        ss << "line " << _lineno << ": " << "Factor::";

        if(_value < 0)
        {
            if(Symbol::Ptr i = _identifier.lock())
            {
                ss << "Identifier::" << i->GetValue();
            }
        }
        else
        {
            ss << "Value::" << _value;
        }
        return ss.str();  
    }

    int Execute(){}

    int _value;
    Symbol::WeakPtr _identifier;
    int const _lineno; 


};


#endif /* end of include guard: _ASTVISITOR */
