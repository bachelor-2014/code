all: test.out

test.out: rucola.l rucola.y test.cpp Absyn.cpp rucola.cpp ../utils/errors.cpp
	/usr/local/bin/bison -d rucola.y -v
	flex  --header-file=lex.yy.h rucola.l
	mv rucola.tab.c rucola.tab.cpp
	mv lex.yy.c lex.yy.cpp
	g++ ../utils/errors.cpp Absyn.cpp rucola.tab.cpp lex.yy.cpp rucola.cpp test.cpp -lfl -o test.out -std=c++0x

clean:
	rm rucola.tab.h rucola.tab.c lex.yy.c lex.yy.h test.out
