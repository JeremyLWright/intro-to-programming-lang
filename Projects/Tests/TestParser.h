#ifndef _TESTPARSER
#define _TESTPARSER

#include <gtest/gtest.h>
#include <string>
using namespace std;
#include "XParser.hpp"
#include "XLexer.hpp"

class ParserTestFixture : public ::testing::Test {
    protected:
        virtual void SetUp()
        {
        }

        virtual void TearDown()
        {
        }
        YY_BUFFER_STATE bp;
};

#endif /* end of include guard: _TESTPARSER */
