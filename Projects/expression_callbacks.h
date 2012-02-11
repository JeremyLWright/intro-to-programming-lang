#ifndef _EXPRESSION_CALLBACKS
#define _EXPRESSION_CALLBACKS

#ifdef __cplusplus
extern "C" {
#endif

#define YYSTYPE int
#define YYERROR_VERBOSE
extern int current_line_number;
   
extern YYSTYPE yyerror (char* s);  /* Called by yyparse on error */
extern YYSTYPE parse_complete(YYSTYPE const result);
extern YYSTYPE parathetical_expr(YYSTYPE const a);
extern YYSTYPE percent_expr(YYSTYPE const a);
extern YYSTYPE at_expr(YYSTYPE const a, YYSTYPE const b);
extern YYSTYPE ampr_expr(YYSTYPE const a, YYSTYPE const b);


#ifdef __cplusplus
}
#endif
#endif /* end of include guard: _EXPRESSION_CALLBACKS */
