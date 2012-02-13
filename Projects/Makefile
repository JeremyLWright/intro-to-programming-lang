CC = g++
CCFLAGS= -O2
YACC= bison 
YFLAGS= -d -t

a.out: ast_parser.tab.o ast_parser.o
	${CC} ${CCFLAGS} ast_parser.tab.o ast_parser.o -o a.out

ast_parser.o: ast_parser.cpp ast_parser.h
	${CC} ${CCFLAGS} -c ast_parser.cpp

ast_parser.tab.o: ast_parser.ypp
	${YACC} ${YFLAGS} ast_parser.ypp
	${CC} ${CCFLAGS} ast_parser.tab.cpp -c 

clean:
	rm -f ast_parser.tab.* *.o ast_parser
