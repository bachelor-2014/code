all: test.out

test.out: splot.l splot.y test.cpp util.cpp Absyn.cpp
	bison -d splot.y
	flex splot.l
	g++ util.cpp Absyn.cpp splot.tab.c lex.yy.c test.cpp -lfl -o test.out -std=c++0x

clean:
	rm splot.tab.h splot.tab.c lex.yy.c test.out
