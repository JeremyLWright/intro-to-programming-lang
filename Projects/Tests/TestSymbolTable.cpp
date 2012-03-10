#include "TestSymbolTable.h"

/* Model this code
* int x = 5;
* int y = 10;
*/
TEST_F(SymbolTableTestFixture, GlobalScope)
{
    //Do not create a scope, use the default global scope.
    myTable->AddSymbol("x");
    myTable->GetSymbol("x")->SetValue(5);
    myTable->AddSymbol("y");
    myTable->GetSymbol("y")->SetValue(10);


    EXPECT_EQ("x", myTable->GetSymbol("x")->GetName());
    EXPECT_EQ(5, myTable->GetSymbol("x")->GetValue());
    EXPECT_EQ("y", myTable->GetSymbol("y")->GetName());
    EXPECT_EQ(10, myTable->GetSymbol("y")->GetValue());
}

/* Model this code
 * int x = 5;
 * int y = 10;
 * {
 *      int x = 7;
 *      int y = 11;
 *      int z = 0;
 * }
 */
TEST_F(SymbolTableTestFixture, OneScopeWithMasking)
{
    //Do not create a scope, use the default global scope.
    myTable->AddSymbol("x");
    myTable->GetSymbol("x")->SetValue(5);
    myTable->AddSymbol("y");
    myTable->GetSymbol("y")->SetValue(10);
    
    // Leave Global Scope
    myTable->EnterScope();

    myTable->AddSymbol("x");
    myTable->GetSymbol("x")->SetValue(7);
    myTable->AddSymbol("y");
    myTable->GetSymbol("y")->SetValue(11);
    myTable->AddSymbol("z");
    myTable->GetSymbol("z")->SetValue(0);

    //Verify Inner Scope
    EXPECT_EQ("x", myTable->GetSymbol("x")->GetName());
    EXPECT_EQ(7, myTable->GetSymbol("x")->GetValue());
    EXPECT_EQ("y", myTable->GetSymbol("y")->GetName());
    EXPECT_EQ(11, myTable->GetSymbol("y")->GetValue());
    EXPECT_EQ("z", myTable->GetSymbol("z")->GetName());
    EXPECT_EQ(0, myTable->GetSymbol("z")->GetValue());
    //Done verify Inner Scope

    myTable->ExitScope();

    //In Global Scope now...
    EXPECT_EQ("x", myTable->GetSymbol("x")->GetName());
    EXPECT_EQ(5, myTable->GetSymbol("x")->GetValue());
    EXPECT_EQ("y", myTable->GetSymbol("y")->GetName());
    EXPECT_EQ(10, myTable->GetSymbol("y")->GetValue());
}

/* Model this code
 * int x = 5;
 * int y = 10;
 * int z = 2;
 * {
 *      int x = 7;
 *      int y = 11;
 * }
 */
TEST_F(SymbolTableTestFixture, OneScopeWithOuterScopeAccess)
{
    //Do not create a scope, use the default global scope.
    myTable->AddSymbol("x");
    myTable->GetSymbol("x")->SetValue(5);
    myTable->AddSymbol("y");
    myTable->GetSymbol("y")->SetValue(10);
    myTable->AddSymbol("z");
    myTable->GetSymbol("z")->SetValue(2);
    
    // Leave Global Scope
    myTable->EnterScope();

    myTable->AddSymbol("x");
    myTable->GetSymbol("x")->SetValue(7);
    myTable->AddSymbol("y");
    myTable->GetSymbol("y")->SetValue(11);

    //Verify Inner Scope
    EXPECT_EQ("x", myTable->GetSymbol("x")->GetName());
    EXPECT_EQ(7, myTable->GetSymbol("x")->GetValue());
    EXPECT_EQ("y", myTable->GetSymbol("y")->GetName());
    EXPECT_EQ(11, myTable->GetSymbol("y")->GetValue());
    EXPECT_EQ("z", myTable->GetSymbol("z")->GetName());
    EXPECT_EQ(2, myTable->GetSymbol("z")->GetValue());
    //Done verify Inner Scope

    myTable->ExitScope();

    //In Global Scope now...
    EXPECT_EQ("x", myTable->GetSymbol("x")->GetName());
    EXPECT_EQ(5, myTable->GetSymbol("x")->GetValue());
    EXPECT_EQ("y", myTable->GetSymbol("y")->GetName());
    EXPECT_EQ(10, myTable->GetSymbol("y")->GetValue());
    EXPECT_EQ("z", myTable->GetSymbol("z")->GetName());
    EXPECT_EQ(2, myTable->GetSymbol("z")->GetValue());
}
