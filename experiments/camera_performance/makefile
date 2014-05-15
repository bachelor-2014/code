LIBS=`pkg-config --libs --cflags opencv cvblob`

all: performance.out

.PHONY: clean

performance.out: performance.cpp
	g++ -o performance.out performance.cpp $(LIBS)

clean:
	rm performance.out
