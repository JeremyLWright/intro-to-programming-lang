using namespace std;
#include <string>
#include "XParser.hpp"
#include "SymbolTable.h"

extern int yyparse(void);
extern SymbolTable::Ptr programSymbolTable;
extern "C" 
{
int yylex();
void yyerror (char* s);
extern int yylineno;
}

int main() {
    programSymbolTable = SymbolTable::construct();
    yylineno = 1;
  return yyparse();
}
