%{
#define YYDEBUG 1
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "SymbolTable.h"
using namespace std;
extern "C" 
{
int yylex();
void yyerror (char* s);
extern int yylineno;
}
SymbolTable::Ptr programSymbolTable;
void checkAssignment(string& s);
%}

%union {
    int token;
    string* s;
    int num;
}

%token <s> TIDENTIFIER
%token <num> TNUMBER
%token <token> TARROW TAMPOP TPEROP TATOP TASSIGN TEQ RELOP CONST VAR COMMA PRINT IF DO END LOOP LPAREN RPAREN

%start Program

%%
Program : Block

Block : /* Epsilon */
      | Block Declaration 
      | Block Statement 


Declaration : VariableDeclaration
            | ConstantDeclaration 

VariableDeclaration : VAR TIDENTIFIER {  programSymbolTable->AddSymbol(*$2); }
                    | COMMA TIDENTIFIER {  programSymbolTable->AddSymbol(*$2); }

ConstantDeclaration : CONST TIDENTIFIER TEQ TNUMBER { programSymbolTable->AddSymbol(*$2, $4, true);}

Statement : Assignment 
            | PrintStmt 
            | IfStmt 
            | DoStmt

Assignment : TIDENTIFIER TASSIGN { checkAssignment(*$1) } Expression
PrintStmt : PRINT Expression

IfStmt : IF Condition END {programSymbolTable->ExitScope();}

DoStmt : LOOP Condition END {programSymbolTable->ExitScope();} 

Condition : /* Epsilon */
            | Condition DO Expression TARROW Block END

Expression : Simple ExpressionOptional

ExpressionOptional : /* Epsilon */
                   | RELOP Simple

Simple : UniTerm SimpleRecurse

SimpleRecurse :  /* Epsilon */
              | SimpleRecurse TAMPOP UniTerm

UniTerm : TPEROP UniTerm 
        | Term

Term : Factor TermOptional

TermOptional : /* Epsilon */
             | TATOP Term

Factor : LPAREN Expression RPAREN
        | TNUMBER
        | TIDENTIFIER
%%

/* Called by yyparse on error */
void yyerror (char* s)  
{
    cout << "line " << yylineno << ": " << s << endl;
}

void checkAssignment(string& s)
{
    if(programSymbolTable->GetSymbol(s)->GetConstness())
    {
        cout << "line " << (yylineno) << ": static semantic error - invalid assignment" << endl;
    }
}
