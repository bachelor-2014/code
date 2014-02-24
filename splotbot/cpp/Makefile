CPPFLAGS = -ggdb -std=c++0x -lm -pthread
OBJS = cJSON.o instructionbuffer.o singlesteppermotor.o splotbot.o

all: test.out

test.out: test.cpp $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) test.cpp -o test.out

cJSON.o: libraries/cJSON/cJSON.h libraries/cJSON/cJSON.c
	g++ $(CPPFLAGS) -c libraries/cJSON/cJSON.c 

instructionbuffer.o: instructionbuffer.h instructionbuffer.cpp
	g++ $(CPPFLAGS) -c instructionbuffer.cpp

singlesteppermotor.o: singlesteppermotor.h singlesteppermotor.cpp
	g++ $(CPPFLAGS) -c singlesteppermotor.cpp

splotbot.o: splotbot.h splotbot.cpp
	g++ $(CPPFLAGS) -c splotbot.cpp
