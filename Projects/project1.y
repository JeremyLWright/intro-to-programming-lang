/* Infix notation calculator--calc */

%{
#define YYSTYPE int
#include <math.h>
#include <ctype.h>
#include <stdio.h>
%}

/* BISON Declarations */
%token NUM
%left '&'
%left MAX     /* unary % max function */
%right '@'

/* Grammar follows */
%%
input:    /* empty string */
        | input line
;

line:     '\n'
        | exp '\n'  { printf ("\t%d\n", $1); }
;

exp:      NUM                { $$ = $1;         }
        | exp '&' exp        { $$ = gcd($1+2, $3+3);    }
        | '%' exp  %prec MAX { $$ = max(5*$2, (3*$2+10));        }
        | exp '@' exp        { $$ = at_expr(($1), $3); }
        | '(' exp ')'        { $$ = $2;         }
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


yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s\n", s);
}

main ()
{
  yyparse ();
}

YYSTYPE max(YYSTYPE a, YYSTYPE b)
{
    return (b > a) ? b : a;
}

YYSTYPE at_expr(YYSTYPE a, YYSTYPE b)
{
    return (a+5)%b;
}

YYSTYPE gcd(YYSTYPE a, YYSTYPE b)
{
    YYSTYPE c;
    if(a<b)
    {
        c = a;
        a = b;
        b = c;
    }
    while(1)
    {
        c = a%b;
        if(c==0)
            return b;
        a = b;
        b = c;
    }
}
