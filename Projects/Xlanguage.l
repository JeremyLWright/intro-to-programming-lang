%option noyywrap yylineno
%{
#include <iostream>
using namespace std;
#include "ASTVisitor.hpp"
#include "XParser.hpp"
#include "SymbolTable.h"
extern SymbolTable::Ptr programSymbolTable;
extern "C"
{
  int yylex();
}

#define SAVE_TOKEN yylval.s = new string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

%}

%%
"("                     return TOKEN(LPAREN);
")"                     return TOKEN(RPAREN);
","                     return TOKEN(COMMA);
[ \t\n]     ; //Ignore White Space
"var"                   return TOKEN(VAR);
"const"                 return TOKEN(CONST);
"print"                 return TOKEN(PRINT);
"if"                    return TOKEN(IF);
"do"                    return TOKEN(DO);
"end"                   return TOKEN(END);
"loop"                  return TOKEN(LOOP);
[a-zA-Z_][a-zA-Z_]*  {   if(yyleng > 20) 
                            {
                                cout << "line " << yylineno << ": lexical error - exceeding maximum token length" << endl;
                                yylval.s = new string(yytext, 20);
                            }
                            else
                            {
                                yylval.s = new string(yytext, yyleng);
                            }
                            return TIDENTIFIER;
                        }
[0-9]+                  {
                            string* s; 
                            if(yyleng > 20) 
                            {
                                cout << "line " << yylineno << ": lexical error - exceeding maximum token length" << endl;
                                s = new string(yytext, 20);
                            }
                            else
                            {
                                s = new string(yytext, yyleng);
                            }
                            yylval.num = atoi(s->c_str());
                            return TNUMBER;
                        }
"->"                    return TOKEN(TARROW);
"&"                     return TOKEN(TAMPOP);
"%"                     return TOKEN(TPEROP);
"@"                     return TOKEN(TATOP);
":="                    return TOKEN(TASSIGN);
"/="                    { yylval.relOp = N_EQ; return RELOP; }
"<="                    { yylval.relOp = LT_EQ; return RELOP; }
">="                    { yylval.relOp = GT_EQ; return RELOP; }
">"                     { yylval.relOp = GT;    return RELOP; }
"<"                     { yylval.relOp = LT;    return RELOP; }
"="                     { yylval.relOp = IS_EQ; return TEQ; }
. cout << "line " << yylineno << ": lexical error - illegal tokens" << endl;
%%
/*
int main()
{
    for(yyFlexLexer l; l.yylex(); )
    {
    }
    return 0;
}*/

