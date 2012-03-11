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

VariableDeclaration : VAR TIDENTIFIER {  checkDeclaration(*$2); }
                    | COMMA TIDENTIFIER {  checkDeclaration(*$2); }

ConstantDeclaration : CONST TIDENTIFIER TEQ TNUMBER { checkConstDeclaration(*$2, $4, true);}

Statement : Assignment 
            | PrintStmt 
            | IfStmt 
            | DoStmt

Assignment : TIDENTIFIER {variableDeclaredLine = yylineno} TASSIGN { checkAssignment(*$1) } Expression
PrintStmt : PRINT Expression 

IfStmt : IF {programSymbolTable->EnterScope();} Condition END {programSymbolTable->ExitScope();}

DoStmt : LOOP {programSymbolTable->EnterScope();} Condition END {programSymbolTable->ExitScope();} 

Condition : /* Epsilon */
            | Condition DO {programSymbolTable->EnterScope();} Expression TARROW Block END  {programSymbolTable->ExitScope();} 

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
        | TIDENTIFIER { checkExistance(*$1); }
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

void checkDeclaration(string const & s)
{
    try 
    {
        programSymbolTable->AddSymbol(s);  
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
    }
    catch (IdentifierUndefined const & e)
    {
        cout << "line " << yylineno << ": static semantic error - identifier undefined" << endl;
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
