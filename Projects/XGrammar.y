%{
#define YYDEBUG 1
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "SymbolTable.h"
#include "ASTVisitor.hpp"
using namespace std;
extern "C" 
{
int yylex();
void yyerror (char* s);
}
extern int yylineno;
SymbolTable::Ptr programSymbolTable;
void checkAssignment(string const & s);
void checkDeclaration(string const & s);
void checkConstDeclaration(string const & s, Symbol::valueType v, bool isConst);
void checkExistance(string const & s); 
int variableDeclaredLine = 0;

%}

%union {
    int token;
    string* s;
    int num;
    RelationalOperator_t relOp;

    /* AST Symbols */
    Factor *factor_t;
    Expression *expression_t;
    Assignment *assignment_t;
    Statement *statement_t;
    Declaration *declaration_t;
    Program *program_t;
    LoopStatement *loopstatement_t;
    Block *block_t;
    Condition *condition_t;
}

%token <s> TIDENTIFIER
%token <num> TNUMBER
%token <token> TARROW TASSIGN TEQ RELOP CONST VAR COMMA PRINT IF DO END LOOP LPAREN RPAREN
%right <token> TATOP
%left <token> TAMPOP TPEROP

/* AST Symbols */
%type <statement_t> Statement Assignment PrintStmt IfStmt DoStmt;
%type <expression_t> Factor Expression Simple UniTerm Term;
%type <program_t> Program;
%type <block_t> Block;
%type <declaration_t> Declaration VariableDeclaration ConstantDeclaration
%type <condition_t> Condition;

%start Program

%%
Program : Block { $$ = new Program($1); $$->Execute();  }

Block : /* Epsilon */ {$$ = new Block(); }
      | Block Declaration { $1->DeclarationList.push_back($2);  }
      | Block Statement { $1->StatementList.push_back($2); }


Declaration : VariableDeclaration
            | ConstantDeclaration  

VariableDeclaration : VAR TIDENTIFIER {  $$ = new VariableDeclaration(*$2); }
                    | COMMA TIDENTIFIER {  $$ = new VariableDeclaration(*$2); }

ConstantDeclaration : CONST TIDENTIFIER TEQ TNUMBER { $$ = new ConstantDeclaration(*$2, $4);}

Statement : Assignment
	| PrintStmt
    | IfStmt
    | DoStmt

Assignment : TIDENTIFIER TASSIGN Expression { $$ = new Assignment(*$1, $3 ); } 

PrintStmt : PRINT Expression { $$ = new PrintStmt($2); }

IfStmt : IF Condition END { $$ = new IfStmt($2); }

DoStmt : LOOP Condition END { $$ = new LoopStatement($2); }

Condition : /* Epsilon */ {$$ = new Condition();}
            | Condition DO Expression TARROW Block END {$1->ConditionSetList.push_back(make_pair($3, $5)); }


Expression : Simple
           | Simple RELOP Simple { $$ = new Comparison($1, $3, static_cast<RelationalOperator_t>($2)); }
           | Simple TEQ Simple { $$ = new Comparison($1, $3, static_cast<RelationalOperator_t>($2)); }

Simple : UniTerm 
       | Simple TAMPOP UniTerm { $$ = new AmpersandExpression($1, $3); }

UniTerm : TPEROP UniTerm { $$  = new PercentExpression($2); }
        | Term 

Term : Factor 
     | Factor TATOP Term {$$ = new AtExpression($1, $3); }

Factor : LPAREN Expression RPAREN { $$ = $2; }
        | TNUMBER { $$ = new Factor($1); }
        | TIDENTIFIER { 
            $$ = new Factor(*$1);
             }
%%

/* Called by yyparse on error */
void yyerror (char* s)  
{
    cout << "line " << yylineno << ": " << s << endl;
}

void checkAssignment(string const & s)
{
    if(programSymbolTable->GetSymbol(s)->GetConstness())
    {
        cout << "line " << (variableDeclaredLine) << ": static semantic error - invalid assignment" << endl;
    }
}
#if 0
void checkDeclaration(string const & s)
{
    try 
    {
        programSymbolTable->AddSymbol(s);  
    } 
    catch (IdentifierRedefined const & e)
    {
        cout << "line " << yylineno << ": static semantic error - identifier redefined" << endl;
        exit(1);
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

void checkConstDeclaration(string const & s, Symbol::valueType v, bool isConst)
{
    try 
    {
        programSymbolTable->AddSymbol(s, v, isConst);  
    } 
    catch (IdentifierRedefined const & e)
    {
        cout << "line " << yylineno << ": static semantic error - identifier redefined" << endl;
        exit(1);
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

void checkExistance(string const & s)
{
    try
    {
        programSymbolTable->GetSymbol(s);
    }
    catch(IdentifierUndefined const & e)
    {
        cout << "line " << yylineno << ": static semantic error - identifier undefined" << endl;
        exit(1); 
    }
}
#endif
