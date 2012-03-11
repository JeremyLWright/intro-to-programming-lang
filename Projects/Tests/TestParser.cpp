#include "TestParser.h"

extern int yyparse(void);

TEST_F(ParserTestFixture, ConstExpr)
{
    char* constExpression = "const N = 10";
    bp = yy_scan_string(constExpression);
    yy_switch_to_buffer(bp);
    yyparse();
}


TEST_F(ParserTestFixture, Loop)
{
    char* constExpression = 
"const N = 10\n\
var i\n\
if\n\
    do 1 -> \n\
        var N\n\
        N := i & 1\n\
    end\n\
end\n\
print N";
    bp = yy_scan_string(constExpression);
    yy_switch_to_buffer(bp);
    yyparse();
}

TEST_F(ParserTestFixture, SimpleAmpersandOperator)
{
    char* constExpression = "N := i & 1";
    bp = yy_scan_string(constExpression);
    yy_switch_to_buffer(bp);
    yyparse();
}

TEST_F(ParserTestFixture, ExampleTest15)
{
    char* constExpression = "const x = 1\n\
  var i, j\n\
  i := i & j & 1040 @ (((100)))\n\
  if\n\
     do i > 20 & %%j -> var k  print  k & (((i)))  end\n\
     do i > 30 & %%j -> var k  print  k & ((j))  end\n\
     do i > 40 & %%j -> var k  print  k & (x)  end\n\
  end\n\
";
    bp = yy_scan_string(constExpression);
    yy_switch_to_buffer(bp);
    yyparse();
}

  

