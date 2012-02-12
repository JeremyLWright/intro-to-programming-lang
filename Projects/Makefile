all: project1.tab.o expression_callbacks.o
	g++  project1.tab.o expression_callbacks.o -lm -o algcalc

project1.tab.o: project1.tab.c
	g++ project1.tab.c -c

project1.tab.c: project1.y
	bison project1.y

expression_callbacks.o: expression_callbacks.cpp expression_callbacks.h
	g++ expression_callbacks.cpp -c

clean:
	rm -rf *.o project1.tab.c



