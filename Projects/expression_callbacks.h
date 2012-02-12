#ifndef _EXPRESSION_CALLBACKS
#define _EXPRESSION_CALLBACKS


#define YYSTYPE int
#define YYERROR_VERBOSE

using namespace std;

struct exp_node {
    YYSTYPE num;
    virtual void print();
    virtual YYSTYPE evaluate();
};

struct operator_node : public exp_node {
    exp_node* left;
    exp_node* right;

    operator_node(exp_node* L, exp_node* R);
};

struct percent_node : public exp_node {
    exp_node* exp;
    void print();
    YYSTYPE evaluate();
    percent_node(exp_node* R);
};

struct ampr_node : public operator_node {
    ampr_node(exp_node* L, exp_node* R);
    void print();
    YYSTYPE evaluate();

};

struct at_node : public operator_node {
    at_node(exp_node* L, exp_node* R);
    void print();
    YYSTYPE evaluate();
};

struct number_node : public exp_node {
    number_node(exp_node* r);
};

extern int current_line_number;
extern exp_node *root;

extern YYSTYPE yyerror (char* s);  /* Called by yyparse on error */
extern YYSTYPE parse_complete(YYSTYPE const result);
extern YYSTYPE parathetical_expr(YYSTYPE const a);
extern YYSTYPE percent_expr(YYSTYPE const a);
extern YYSTYPE at_expr(YYSTYPE const a, YYSTYPE const b);
extern YYSTYPE ampr_expr(YYSTYPE const a, YYSTYPE const b);


#endif /* end of include guard: _EXPRESSION_CALLBACKS */
