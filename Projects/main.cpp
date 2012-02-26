/**
 * @brief Main entry point for the Project Compiler
 *
 * @par
 * Copyright Jeremy Wright (c) 2012
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#include <iostream>
using namespace std;

int yyparse();

int main()
{
    yyparse(); //Just run the parser. The Parser drives the whole program
    //The example test files have 1 empty newline at the very end of the file.
    cout << endl; // :-(
}

