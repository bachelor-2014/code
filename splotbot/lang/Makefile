all: splotlang.out

splotlang.out: splot.l splot.y splotlang.cpp
	bison -d splot.y
	flex splot.l
	g++ splot.tab.c lex.yy.c splotlang.cpp -lfl -o splotlang.out -std=c++0x
clean:
	rm splot.tab.h splot.tab.c lex.yy.c
