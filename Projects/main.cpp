using namespace std;
#include <string>
#include "XParser.hpp"
#include "XLexer.hpp"
#include "SymbolTable.h"

extern int yyparse(void);
extern SymbolTable::Ptr programSymbolTable;
extern "C" 
{
void yyerror (char* s);
}

int main(int argc, char* argv[]) {
    programSymbolTable = SymbolTable::construct();
    yylineno = 1;
    YY_BUFFER_STATE bp;
    FILE* f;
    if(argc == 2) //Enter test mode
    {
        f = fopen(argv[1], "r");
        bp = yy_create_buffer(f, YY_BUF_SIZE);
        yy_switch_to_buffer(bp);
    }
  return yyparse();
}
