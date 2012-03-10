%option noyywrap debug

%{
#include <iostream>
using namespace std;
#include "XParser.hpp"
extern "C"
{
  int yylex();
}

#define SAVE_TOKEN yylval.s = new string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

%}

%%

","                     return TOKEN(COMMA);
[ \t\n]     ; //Ignore White Space
"var"                   return TOKEN(KW_VAR);
"const"                 return TOKEN(KW_CONST);
[a-zA-Z_][a-zA-Z0-9_]*  {   if(yyleng > 20) 
                            {
                                cout << "line " << 0 << ": lexical error - exceeding maximum token length" << endl;
                                yylval.s = new string(yytext, 20);
                            }
                            else
                            {
                                yylval.s = new string(yytext, yyleng);
                            }
                            return TIDENTIFIER;
                        }
[0-9]+                  SAVE_TOKEN; return TNUMBER;
"->"                    return TOKEN(TARROW);
"&"                     return TOKEN(TAMPOP);
"%"                     return TOKEN(TPEROP);
"@"                     return TOKEN(TATOP);
":="                    return TOKEN(TASSIGN);
"/="                    return TOKEN(RELOP);
"<="                    return TOKEN(RELOP);
">="                    return TOKEN(RELOP);
"="                     return TOKEN(TEQ);
. cout << "line " << 0 << ": lexical error - illegal tokens" << endl;
%%
/*
int main()
{
    for(yyFlexLexer l; l.yylex(); )
    {
    }
    return 0;
}*/

