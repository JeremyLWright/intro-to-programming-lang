all: project1.tab.o expression_callbacks.o
	gcc  project1.tab.o expression_callbacks.o -lm -o algcalc

project1.tab.o: project1.tab.c
	gcc project1.tab.c -c

project1.tab.c: project1.y
	bison project1.y

expression_callbacks.o: expression_callbacks.cpp expression_callbacks.h
	g++ expression_callbacks.cpp -c

clean:
	rm -rf *.o



