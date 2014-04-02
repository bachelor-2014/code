libs = `pkg-config --libs --cflags opencv` -lpthread

default: mendel.out

command = g++ -std=c++0x -ggdb

mendel.out: mendel.cpp mendel.elf
	$(command) -o mendel.out mendel.cpp

