libs = `pkg-config --libs --cflags opencv`

command = gcc

%.out: %.c
	$(command) -o $@ $^ $(libs)

clean:
	#find -name "*.out" | xargs rm
