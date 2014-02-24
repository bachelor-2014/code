all: test.out

test.out: test.cpp splotbot.cpp splotbot.h instructionbuffer.cpp instructionbuffer.h
	g++ -ggdb -std=c++0x -pthread instructionbuffer.cpp splotbot.cpp test.cpp -o test.out
