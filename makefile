CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPS = backwards.h forward.h structures.h traitement.h save.h terminal_menu.c
OBJ = main.o backwards.o forward.o traitement.o save.o terminal_menu.o

all: compile

clean:
	rm -f $(OBJ) main

compile: clean main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

valgrind: main
	valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./main