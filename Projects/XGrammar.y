%{
#define YYDEBUG 1
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
extern "C" 
{
int yylex();
void yyerror (char* s);
extern int yylineno;
}

%}

%union {
    int token;
    string* s;
    int placeholder;
}
%error-verbose

%token <s> TIDENTIFIER TNUMBER
%token <token> TARROW TAMPOP TPEROP TATOP TASSIGN TEQ RELOP CONST VAR COMMA PRINT IF DO END LOOP LPAREN RPAREN
%type<placeholder> ConstantDeclaration Program Declaration

%start Program

%%
Program : Block{ cout << "Program" << endl;}

Block : /* Epsilon */
      | Block Declaration 
      | Block Statement { cout << "Block" << endl;}


Declaration : VariableDeclaration { cout << "Variable Declaration" << endl;}
            | ConstantDeclaration { cout << "Declaration" << endl;}

VariableDeclaration : VAR TIDENTIFIER {  cout << *$2 <<"<-- Single Variable "  <<  endl}
                    | COMMA TIDENTIFIER {  cout << *$2 <<"<-- Part of List Variable "  <<  endl}

ConstantDeclaration : CONST TIDENTIFIER TEQ TNUMBER { cout << "const " << *$2 << " is " << *$4  << endl;}

Statement : Assignment 
            | PrintStmt 
            | IfStmt 
            | DoStmt

Assignment : TIDENTIFIER TASSIGN Expression

PrintStmt : PRINT Expression

IfStmt : IF Condition END

DoStmt : LOOP Condition END

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
    //Look through the error message from bison, if it says $undefined then we have a "lexical error"
    //if it says $undefined then we have a "lexical error"
    //Otherwise we have a "syntax error"
    cout << s << endl;
/*
    if(strstr(s, "undefined") != NULL)
    {
        printf("line %d lexical error\n", 1);
    }
    else
    {
        printf("line %d syntax error\n", 1);
    }
*/
}
