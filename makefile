CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEPS = backwards.h forward.h structures.h traitement.h save.h
OBJ = main.o backwards.o forward.o traitement.o save.o

all: compile

clean:
	rm -f $(OBJ) main

compile: clean main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)