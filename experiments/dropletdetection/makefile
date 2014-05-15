LIBS = `pkg-config --libs --cflags opencv cvblob`
SRCS = filters.cpp
OUTS = $(SRCS:.cpp=.out)

all: filters.out

.PHONY: clean

results:
	-@mkdir results/
filters.out: filters.cpp results
	g++ -o $@ filters.cpp $(LIBS)

clean:
	rm performance.out
