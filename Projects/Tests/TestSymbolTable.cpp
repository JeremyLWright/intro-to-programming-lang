#include "TestSymbolTable.h"
#include <stdexcept>

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

/* Model this code
 * int x = 1;
 * int y = 2;
 * int z = 3;
 * { //1
 *      int a = 4;
 *      int b = 5;
 *      {  //2
 *          int c = 6;
 *          int d = 7;
 *              { //3
 *                  int c = 8;
 *              } //3
 *          int e = 9;
 *      } //2
 * } //1
 */
TEST_F(SymbolTableTestFixture, DeepScopeWithMultipleAccess)
{
    //Do not create a scope, use the default global scope.
    myTable->AddSymbol("x", 1);
    myTable->AddSymbol("y", 2);
    myTable->AddSymbol("z", 3);
    
    // Leave Global Scope
    myTable->EnterScope(); // Scope 1
    {

        myTable->AddSymbol("a", 4);
        myTable->AddSymbol("b", 5);

        EXPECT_EQ(1, myTable->GetSymbol("x")->GetValue());
        EXPECT_EQ(2, myTable->GetSymbol("y")->GetValue());
        EXPECT_EQ(3, myTable->GetSymbol("z")->GetValue());
        EXPECT_EQ(4, myTable->GetSymbol("a")->GetValue());
        EXPECT_EQ(5, myTable->GetSymbol("b")->GetValue());

        myTable->EnterScope(); //Scope 2
        {

            myTable->AddSymbol("c", 6);
            myTable->AddSymbol("d", 7);

            EXPECT_EQ(1, myTable->GetSymbol("x")->GetValue());
            EXPECT_EQ(2, myTable->GetSymbol("y")->GetValue());
            EXPECT_EQ(3, myTable->GetSymbol("z")->GetValue());
            EXPECT_EQ(4, myTable->GetSymbol("a")->GetValue());
            EXPECT_EQ(5, myTable->GetSymbol("b")->GetValue());
            EXPECT_EQ(6, myTable->GetSymbol("c")->GetValue());
            EXPECT_EQ(7, myTable->GetSymbol("d")->GetValue());

            myTable->EnterScope(); //Scope 3
            {

                myTable->AddSymbol("c", 8);

                EXPECT_EQ(1, myTable->GetSymbol("x")->GetValue());
                EXPECT_EQ(2, myTable->GetSymbol("y")->GetValue());
                EXPECT_EQ(3, myTable->GetSymbol("z")->GetValue());
                EXPECT_EQ(4, myTable->GetSymbol("a")->GetValue());
                EXPECT_EQ(5, myTable->GetSymbol("b")->GetValue());
                EXPECT_EQ(8, myTable->GetSymbol("c")->GetValue());
                EXPECT_EQ(7, myTable->GetSymbol("d")->GetValue());
            }
            myTable->ExitScope(); // Scope 3
            myTable->AddSymbol("e", 9);
            
            EXPECT_EQ(1, myTable->GetSymbol("x")->GetValue());
            EXPECT_EQ(2, myTable->GetSymbol("y")->GetValue());
            EXPECT_EQ(3, myTable->GetSymbol("z")->GetValue());
            EXPECT_EQ(4, myTable->GetSymbol("a")->GetValue());
            EXPECT_EQ(5, myTable->GetSymbol("b")->GetValue());
            EXPECT_EQ(6, myTable->GetSymbol("c")->GetValue());
            EXPECT_EQ(7, myTable->GetSymbol("d")->GetValue());
            EXPECT_EQ(9, myTable->GetSymbol("e")->GetValue());

        } 
        myTable->ExitScope(); //Scope 2
        EXPECT_EQ(1, myTable->GetSymbol("x")->GetValue());
        EXPECT_EQ(2, myTable->GetSymbol("y")->GetValue());
        EXPECT_EQ(3, myTable->GetSymbol("z")->GetValue());
        EXPECT_EQ(4, myTable->GetSymbol("a")->GetValue());
        EXPECT_EQ(5, myTable->GetSymbol("b")->GetValue());
        EXPECT_THROW(myTable->GetSymbol("c")->GetValue(), IdentifierUndefined);
        EXPECT_THROW(myTable->GetSymbol("d")->GetValue(), IdentifierUndefined);
        EXPECT_THROW(myTable->GetSymbol("e")->GetValue(), IdentifierUndefined);

    }
    myTable->ExitScope(); //Scope 1
    EXPECT_EQ(1, myTable->GetSymbol("x")->GetValue());
    EXPECT_EQ(2, myTable->GetSymbol("y")->GetValue());
    EXPECT_EQ(3, myTable->GetSymbol("z")->GetValue());
    EXPECT_THROW(myTable->GetSymbol("a")->GetValue(), IdentifierUndefined);
    EXPECT_THROW(myTable->GetSymbol("b")->GetValue(), IdentifierUndefined);
    EXPECT_THROW(myTable->GetSymbol("c")->GetValue(), IdentifierUndefined);
    EXPECT_THROW(myTable->GetSymbol("d")->GetValue(), IdentifierUndefined);

    //In Global Scope now...

}


TEST_F(SymbolTableTestFixture, RedefineSymbol)
{
    myTable->AddSymbol("y", 6);
    EXPECT_THROW(myTable->AddSymbol("y", 8), IdentifierRedefined);
}

TEST_F(SymbolTableTestFixture, ConstMaskNonConst)
{
    myTable->AddSymbol("N");
    EXPECT_FALSE(myTable->GetSymbol("N")->GetConstness());
    myTable->EnterScope();
    myTable->AddSymbol("N", 5, true);
    EXPECT_TRUE(myTable->GetSymbol("N")->GetConstness());
    myTable->ExitScope();

}


TEST_F(SymbolTableTestFixture, NonConstMaskConst)
{
    myTable->AddSymbol("N", 5, true);
    EXPECT_TRUE(myTable->GetSymbol("N")->GetConstness());
    myTable->EnterScope();
    myTable->AddSymbol("N", 5);
    EXPECT_FALSE(myTable->GetSymbol("N")->GetConstness());
    myTable->ExitScope();

}
