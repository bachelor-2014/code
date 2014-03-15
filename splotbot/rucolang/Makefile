all: test.out

test.out: rucola.l rucola.y test.cpp util.cpp Absyn.cpp
	bison -d rucola.y
	flex rucola.l
	g++ util.cpp Absyn.cpp rucola.tab.c lex.yy.c test.cpp -lfl -o test.out -std=c++0x

clean:
	rm rucola.tab.h rucola.tab.c lex.yy.c test.out
