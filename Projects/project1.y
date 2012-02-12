/* Infix notation calculator--calc */

%{
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "expression_callbacks.h"

using namespace std;

exp_node* root;
int yylex();

%}

%union {
    exp_node* expnode;
    int num;
}

/* BISON Declarations */

%token <expnode> NUM
%left '&'
%left PERCENT_EXPR     /* unary % percent_expr function */
%right '@'
%type <expnode> input
%type <expnode> exp

/* Grammar follows */
%%
input: line {$$ = new exp_node($1); root = $$;}
;

line:     '\n'
        | exp '\n'  { parse_complete($1); }
        | error '\n' { yyerrok } /* continue parsing after an error */
;

exp:      NUM                { $$ = new number_node($1);         }
        | exp '&' exp        { $$ = new ampr_node($1, $3);    }
        | '%' exp  %prec PERCENT_EXPR { $$ = new percent_node($2);        }
        | exp '@' exp        { $$ = new at_node($1, $3); }
        | '(' exp ')'        { $$ = $2        }
;
%%

/* Additional C Code */

int yylex ()
{
  int c;

  /* skip white space  */
  while ((c = getchar ()) == ' ' || c == '\t')  
    ;
  /* process numbers   */
  if (c == '.' || isdigit (c))                
    {
      ungetc (c, stdin);
      scanf ("%d", &yylval);
      return NUM;
    }
  /* return end-of-file  */
  if (c == EOF)                            
    return 0;
  /* return single chars */
  return c;                                
}



main ()
{
  yyparse ();
}

