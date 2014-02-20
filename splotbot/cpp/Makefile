all: test.out

test.out: test.cpp splotbot.cpp splotbot.h
	g++ -ggdb -std=c++0x -pthread splotbot.cpp test.cpp -o test.out
