CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(CSE340_Compiler)
Find_Package(BISON REQUIRED)
Find_Package(FLEX REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
find_package(GTest)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -ggdb -Wall ")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG ")
BISON_TARGET(astParser ast_parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/ast_parser.tab.cpp)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(PROJ_SOURCES ast_parser.cpp ${BISON_astParser_OUTPUTS})
add_executable(a.out main.cpp ${PROJ_SOURCES})

if(GTEST_FOUND)
    ENABLE_TESTING()
    add_custom_target(gtest 
        COMMAND test_ast
        DEPENDS test_ast)
    FILE(GLOB Test_Sources Tests/*.cpp)
    
    add_executable(test_parser ${Test_Sources} ${PROJ_SOURCES})
    target_link_libraries(test_parser ${GTEST_BOTH_LIBRARIES} pthread)
    ADD_TEST(GTest ${CMAKE_CURRENT_BINARY_DIR}/test_parser --gtest_output=xml)

endif()
