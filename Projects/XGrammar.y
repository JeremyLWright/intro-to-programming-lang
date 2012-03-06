%{
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
}

%token <s> TIDENTIFIER TNUMBER
%token <token> TARROW TAMPOP TPEROP TATOP TASSIGN TNEQ TLEQ TGEQ KW_CONST KW_VAR TEQ

%start ConstantDeclaration

%%
ConstantDeclaration : KW_CONST TIDENTIFIER TEQ TNUMBER {  cout << "const " << *$2 << " is " << *$4  << endl};
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
