/* Infix notation calculator--calc */

%{
#define YYSTYPE int
#define YYERROR_VERBOSE
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
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
        | exp '\n'  { printf ("result: %d\n", $1); }
;

exp:      NUM                { $$ = $1;         }
        | exp '&' exp        { $$ = ampr_expr($1, $3);    }
        | '%' exp  %prec PERCENT_EXPR { $$ = percent_expr($2);        }
        | exp '@' exp        { $$ = at_expr($1, $3); }
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
#if 0
  printf ("%s\n", s); //Print the verbose bison error
#else
    //Look through the error message from bison, if it says $undefined then we have a "lexical error"
    //Otherwise we have a "syntax error"
    if(strstr(s, "undefined") != NULL)
    {
        printf("lexical error\n");
    }
    else
    {
        printf("syntax error\n");
    }
#endif
}

main ()
{
  yyparse ();
}

YYSTYPE percent_expr(YYSTYPE const a)
{
    printf( "%% %d\n", a);
    YYSTYPE a2 = 5*a;
    YYSTYPE b = 3*a+10;
    return (b > a2) ? b : a2;
}

YYSTYPE at_expr(YYSTYPE const a, YYSTYPE const b)
{
    printf( "%d @ %d\n", a, b);
    return (a+5)%b;
}

YYSTYPE ampr_expr(YYSTYPE const a, YYSTYPE const b)
{
    YYSTYPE a2 = a+2;
    YYSTYPE b2 = b+3;
    printf( "%d & %d\n", a, b);
    YYSTYPE c;
    if(a2<b2)
    {
        c = a2;
        a2 = b2;
        b2 = c;
    }
    while(1)
    {
        c = a2%b2;
        if(c==0)
            return b2;
        a2 = b2;
        b2 = c;
    }
}
