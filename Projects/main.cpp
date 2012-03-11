using namespace std;
#include <string>
#include "XParser.hpp"

extern int yyparse(void);
extern "C" 
{
int yylex();
void yyerror (char* s);
extern int yylineno;
}

int main() {
    yylineno = 1;
  return yyparse();
}
