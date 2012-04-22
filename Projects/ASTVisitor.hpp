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
#include <cstdlib>
using namespace std;

extern int yylineno;
extern SymbolTable::Ptr programSymbolTable;
struct Program {
    void Execute()
    {

    }
    virtual string ToString()
    {
        return "Program:: ";  
    }
};

struct ASTNode {
    public: 
        virtual string ToString() = 0;
};


struct Block : public ASTNode {
    virtual string ToString()
    {
        return "Block:: ";  
    }
};

struct Declaration : public ASTNode {
    virtual void Execute() = 0;
    virtual string ToString()
    {
        return "Declaration:: ";  
    }
};

struct VariableDeclaration : public Declaration {
    VariableDeclaration(string name) :
        _name(name)
    {
    }

    virtual void Execute()
    {
        try
        {
            programSymbolTable->AddSymbol(_name);
        } 
        catch (IdentifierRedefined const & e)
        {
            cout << "line " << yylineno << ": static semantic error - identifier redefined" << endl;
        }   
        catch (IdentifierUndefined const & e)
        {
            cout << "line " << yylineno << ": static semantic error - identifier undefined" << endl;
            exit(1);
        }
        catch (DeclarationAfterStatement const & e)
        {
            cout << "We're here" << endl;
            cout << "line " << yylineno << ": syntax error" << endl;
            exit(1);
        }   

    }
    virtual string ToString()
    {
        return "VariableDeclaration:: ";  
    }
    string const _name;
};

struct ConstantDeclaration : public Declaration {
    ConstantDeclaration(string name, int value):
        _value(value),
        _name(name)
    {
    }

    virtual void Execute()
    {
        try
        {
            programSymbolTable->AddSymbol(_name, _value, true);
        } 
        catch (IdentifierRedefined const & e)
        {
            cout << "line " << yylineno << ": static semantic error - identifier redefined" << endl;
        }
        catch (IdentifierUndefined const & e)
        {
            cout << "line " << yylineno << ": static semantic error - identifier undefined" << endl;
            exit(1);
        }   
        catch (DeclarationAfterStatement const & e)
        {
            cout << "line " << yylineno << ": syntax error" << endl;
            exit(1);
        }   

    }

    virtual string ToString()
    {
        return "ConstantDeclaration:: ";  
    }
    int const _value;
    string const _name;
};

struct Statement : public ASTNode {
    virtual string ToString()
    {
        return "Statement:: ";  
    }

    virtual void Execute() = 0; 
};

struct Expression : public ASTNode {
    virtual string ToString()
    {
        return "Expression:: ";  
    }
    virtual int Execute() = 0;
    virtual void Print() = 0;
    protected:
    int currentValue;
    virtual void PrintIndentation(int depth=0)
    {
        for(int i = 0; i < depth; ++i)
            cout << "   "; //Example files show 3 spaces per indentation.
    }


};

struct Assignment : public Statement {

    Assignment(string id, Expression* rhs):
        _rhs(rhs),
        _identifier(id)
    {
        cout << "Creating Assignment to: " << _identifier << endl;
    }

    virtual string ToString()
    {
        return "Assignment:: ";  
    }

    virtual void Execute()
    {
        programSymbolTable->GetSymbol(_identifier)->SetValue(_rhs->Execute());
    }

    Expression* _rhs;
    string const _identifier;
};

struct PrintStmt : public Statement {
    PrintStmt(Expression* rhs):
        _rhs(rhs)
    {
    }

    virtual string ToString()
    {
        return "PrintStmt:: ";  
    }

    virtual void Execute()
    {
        cout << _rhs->Execute() << endl;
    }

    Expression* _rhs;
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
    virtual int Execute();
    virtual void Print();
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
    virtual void Print();
    virtual int Execute();
};

struct AtExpression : public OperatorExpression {
    AtExpression(Expression *L, Expression* R):
        OperatorExpression(L, R) {}
    virtual ~AtExpression();
    virtual string ToString()
    {
        return "SimpleExpression:: ";  
    }
    virtual void Print();
    virtual int Execute();
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
    virtual int Execute();
    virtual void Print();
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
        _lineno(yylineno),
        _isLiteralValue(true)
    {
    }

    Factor(string identifier):
        _identifier(identifier),
        _value(-1),
        _lineno(yylineno),
        _isLiteralValue(false)
    {
    }

    virtual string ToString()
    {
#if 0
        stringstream ss;

        ss << "line " << _lineno << ": " << "Factor::";

        if(_isLiteralValue == false)
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
#endif
        return "Factor::";  
    }

    virtual int Execute()
    {
        if(_isLiteralValue == false)
        {
            Symbol::Ptr s = programSymbolTable->GetSymbol(_identifier);
            _value = s->GetValue();
        }

        return _value;
    }

    virtual void Print()
    {
        cout << this->ToString();
    }

    string _identifier;
    int _value;
    int const _lineno; 
    bool const _isLiteralValue;


};


#endif /* end of include guard: _ASTVISITOR */
