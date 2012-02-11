#include "expression_callbacks.h"
#include <cmath>
#include <cstring>
#include <cstdio>

int current_line_number = 1;
   
int yyerror (char* s)  /* Called by yyparse on error */
{
#if 0
  printf ("%s\n", s); //Print the verbose bison error
#else
    //Look through the error message from bison, if it says $undefined then we have a "lexical error"
    //Otherwise we have a "syntax error"
    if(strstr(s, "undefined") != NULL)
    {
        printf("line %d lexical error\n", current_line_number);
    }
    else
    {
        printf("line %d syntax error\n", current_line_number);
    }
#endif
    current_line_number++;
}
 
YYSTYPE parse_complete(YYSTYPE const result)
{
    printf ("result: %d\n", result);
    current_line_number++;
}

YYSTYPE parathetical_expr(YYSTYPE const a)
{
    printf("( %d )\n", a);
    return a;
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

