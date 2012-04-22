%{
#define YYDEBUG 1
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "SymbolTable.h"
#include "ASTVisitor.hpp"
using namespace std;
extern "C" 
{
int yylex();
void yyerror (char* s);
}
extern int yylineno;
SymbolTable::Ptr programSymbolTable;
void checkAssignment(string const & s);
void checkDeclaration(string const & s);
void checkConstDeclaration(string const & s, Symbol::valueType v, bool isConst);
void checkExistance(string const & s); 
int variableDeclaredLine = 0;
typedef vector<Statement*> StatementList_t;
StatementList_t StatementList;
typedef vector<Declaration*> DeclarationList_t;
DeclarationList_t DeclarationList;

%}

%union {
    int token;
    string* s;
    int num;

    /* AST Symbols */
    Factor *factor_t;
    Expression *expression_t;
    Assignment *assignment_t;
    Statement *statement_t;
    Declaration *declaration_t;
    Program *program_t;
}

%token <s> TIDENTIFIER
%token <num> TNUMBER
%token <token> TARROW TASSIGN TEQ RELOP CONST VAR COMMA PRINT IF DO END LOOP LPAREN RPAREN
%right <token> TATOP
%left <token> TAMPOP TPEROP

/* AST Symbols */
%type <statement_t> Statement Assignment PrintStmt IfStmt DoStmt;
%type <expression_t> Factor Expression Simple UniTerm Term;
%type <program_t> Program;
%type <declaration_t> Declaration VariableDeclaration ConstantDeclaration

%start Program

%%
Program : Block { $$ = new Program(); cout << $$->ToString(); 
        for(DeclarationList_t::iterator i = DeclarationList.begin();
                i != DeclarationList.end();
                ++i)
            {
                (*i)->Execute();
            }

        for(StatementList_t::iterator i = StatementList.begin();
                i != StatementList.end();
                ++i)
            {
                (*i)->Execute();
            }
        }

Block : /* Epsilon */
      | Block Declaration { DeclarationList.push_back($2); cout << "Adding Declaration" << endl; }
      | Block Statement { StatementList.push_back($2); cout << "Adding Statement" << endl; }


Declaration : VariableDeclaration
            | ConstantDeclaration  

VariableDeclaration : VAR TIDENTIFIER {  $$ = new VariableDeclaration(*$2); }
                    | COMMA TIDENTIFIER {  $$ = new VariableDeclaration(*$2); }

ConstantDeclaration : CONST TIDENTIFIER TEQ TNUMBER { $$ = new ConstantDeclaration(*$2, $4);}

Statement : Assignment
	| PrintStmt
    | IfStmt
    | DoStmt

Assignment : TIDENTIFIER TASSIGN Expression { $$ = new Assignment(*$1, $3 ); } 

PrintStmt : PRINT Expression { $$ = new PrintStmt($2); }

IfStmt : IF {programSymbolTable->EnterScope();} Condition END {programSymbolTable->ExitScope();}

DoStmt : LOOP {programSymbolTable->EnterScope();} Condition END {programSymbolTable->ExitScope();} 

Condition : /* Epsilon */
            | Condition DO {programSymbolTable->EnterScope();} Expression TARROW Block END  {programSymbolTable->ExitScope();} 


Expression : Simple
           | Simple RELOP Simple { $$ = new Comparison($1, $3, $2); }
           | Simple TEQ Simple { $$ = new Comparison($1, $3, $2); }

Simple : UniTerm 
       | Simple TAMPOP UniTerm { $$ = new AmpersandExpression($1, $3); }

UniTerm : TPEROP UniTerm { $$  = new PercentExpression($2); }
        | Term 

Term : Factor 
     | Factor TATOP Term {$$ = new AtExpression($1, $3); }

Factor : LPAREN Expression RPAREN { $$ = $2; }
        | TNUMBER { $$ = new Factor($1); }
        | TIDENTIFIER { 
            $$ = new Factor(*$1);
             }
%%

/* Called by yyparse on error */
void yyerror (char* s)  
{
    cout << "line " << yylineno << ": " << s << endl;
}

void checkAssignment(string const & s)
{
    if(programSymbolTable->GetSymbol(s)->GetConstness())
    {
        cout << "line " << (variableDeclaredLine) << ": static semantic error - invalid assignment" << endl;
    }
}

void checkDeclaration(string const & s)
{
    try 
    {
        programSymbolTable->AddSymbol(s);  
    } 
    catch (IdentifierRedefined const & e)
    {
        cout << "line " << yylineno << ": static semantic error - identifier redefined" << endl;
    }   
    catch (IdentifierUndefined const & e)
    {
        cout << "line " << yylineno << ": static semantic error - identifier undefined" << endl;
        exit(1);
    }
    catch (DeclarationAfterStatement const & e)
    {
        cout << "We're here" << endl;
        cout << "line " << yylineno << ": syntax error" << endl;
        exit(1);
    }   
}

void checkConstDeclaration(string const & s, Symbol::valueType v, bool isConst)
{
    try 
    {
        programSymbolTable->AddSymbol(s, v, isConst);  
    } 
    catch (IdentifierRedefined const & e)
    {
        cout << "line " << yylineno << ": static semantic error - identifier redefined" << endl;
    }
    catch (IdentifierUndefined const & e)
    {
        cout << "line " << yylineno << ": static semantic error - identifier undefined" << endl;
        exit(1);
    }   
    catch (DeclarationAfterStatement const & e)
    {
        cout << "line " << yylineno << ": syntax error" << endl;
        exit(1);
    }   

}

void checkExistance(string const & s)
{
    try
    {
        programSymbolTable->GetSymbol(s);
    }
    catch(IdentifierUndefined const & e)
    {
        cout << "line " << yylineno << ": static semantic error - identifier undefined" << endl;
        exit(1); 
    }
}
