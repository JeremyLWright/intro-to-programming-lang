#ifndef _TESTPARSER
#define _TESTPARSER

#include <gtest/gtest.h>
#include <string>
using namespace std;
#include "XParser.hpp"
#include "XLexer.hpp"
#include "SymbolTable.h"

extern SymbolTable::Ptr programSymbolTable;

class ParserTestFixture : public ::testing::Test {
    protected:
        virtual void SetUp()
        {
            programSymbolTable = SymbolTable::construct();
        }

        virtual void TearDown()
        {
        }
        YY_BUFFER_STATE bp;
};

#endif /* end of include guard: _TESTPARSER */
