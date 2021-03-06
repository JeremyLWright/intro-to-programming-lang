CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ENABLE_TESTING()
project(CSE340_Compiler)
Find_Package(BISON REQUIRED)
Find_Package(FLEX REQUIRED)
Find_Package(GTest)
#find_package(GTest)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -ggdb -Wall ")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG ")
BISON_TARGET(XParser XGrammar.y ${CMAKE_CURRENT_BINARY_DIR}/XParser.cpp
    COMPILE_FLAGS "-rall" )
FLEX_TARGET(XLexer Xlanguage.l ${CMAKE_CURRENT_BINARY_DIR}/XLexer.cpp
    COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_BINARY_DIR}/XLexer.hpp")
ADD_FLEX_BISON_DEPENDENCY(XLexer XParser)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(HandSources SymbolTable.cpp Symbol.cpp ASTVisitor.cpp)
set(PROJ_SOURCES  ${BISON_XParser_OUTPUTS} ${FLEX_XLexer_OUTPUTS})
add_executable(a.out main.cpp ${PROJ_SOURCES} ${HandSources})
target_link_libraries(a.out ${FLEX_LIBRARIES})

if(GTEST_FOUND)
    ENABLE_TESTING()
    add_custom_target(gtest 
        COMMAND test_ast
        DEPENDS test_ast)
    FILE(GLOB Test_Sources Tests/*.cpp)
    
    add_executable(test_parser ${Test_Sources} ${HandSources} ${BISON_XParser_OUTPUTS} ${FLEX_XLexer_OUTPUTS})
    target_link_libraries(test_parser ${GTEST_BOTH_LIBRARIES} pthread)
    ADD_TEST(GTest ${CMAKE_CURRENT_BINARY_DIR}/test_parser --gtest_output=xml)

endif()

ADD_TEST(Test01 ${CMAKE_CURRENT_BINARY_DIR}/a.out
< ${CMAKE_CURRENT_SOURCE_DIR}/DiffTests/test01.txt)
