PROGRAM=tscheme
OBJECTS=tscheme.o reader.o memory.o object.o
CFLAGS=-g -Wall -O0
LDLIBS=
CC=c99

$(PROGRAM): $(OBJECTS)

.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
