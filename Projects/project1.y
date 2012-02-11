/* Infix notation calculator--calc */

%{
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "expression_callbacks.h"
%}

/* BISON Declarations */
%token NUM
%left '&'
%left PERCENT_EXPR     /* unary % percent_expr function */
%right '@'

/* Grammar follows */
%%
input:    /* empty string */
        | input line
;

line:     '\n'
        | exp '\n'  { parse_complete($1); }
        | error '\n' { yyerrok } /* continue parsing after an error */
;

exp:      NUM                { $$ = $1;         }
        | exp '&' exp        { $$ = ampr_expr($1, $3);    }
        | '%' exp  %prec PERCENT_EXPR { $$ = percent_expr($2);        }
        | exp '@' exp        { $$ = at_expr($1, $3); }
        | '(' exp ')'        { $$ = parathetical_expr($2);         }
;
%%

/* Additional C Code */

yylex ()
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

