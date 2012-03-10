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
}


%}

%union {
    int token;
    string* s;
    int placeholder;
}

%token <s> TIDENTIFIER TNUMBER
%token <token> TARROW TAMPOP TPEROP TATOP TASSIGN TEQ RELOP KW_CONST KW_VAR COMMA
%type<placeholder> ConstantDeclaration Program Block Declaration

%start Program

%%
Program : Block{ $$ = 1; cout << "Program" << endl;}

Block : Declaration | Block Declaration{ $$ = 1; cout << "Block" << endl;}

Declaration : VariableDeclaration | ConstantDeclaration { $$ = 1; cout << "Declaration" << endl;}

VariableDeclaration : KW_VAR VariableDeclaration
                    | COMMA TIDENTIFIER {  cout << *$2 <<"<-- Part of List Variable "  <<  endl}
                    | TIDENTIFIER {  cout << *$1 <<"<-- Single Variable "  <<  endl}

ConstantDeclaration : KW_CONST TIDENTIFIER TEQ TNUMBER {  $$ = 1; cout << "const " << *$2 << " is " << *$4  << endl;}
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

int main() {
  return yyparse();
}
