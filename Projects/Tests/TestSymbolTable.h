#include <gtest/gtest.h>
#include "SymbolTable.h"

class SymbolTableTestFixture : public ::testing::Test {
    protected:
        virtual void SetUp()
        {
            myTable = SymbolTable::construct();
        }

        virtual void TearDown()
        {
        }

        SymbolTable::Ptr myTable;
};
