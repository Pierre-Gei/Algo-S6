CC := gcc
CFLAGS := -Wall -O2 -o
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPS = backwards.h forward.h structures.h traitement.h save.h terminal_menu.c
OBJ = main.o backwards.o forward.o traitement.o save.o terminal_menu.o

BUILDDIR := ./build
INCLUDE := ./include
SRC := ./src
SRCFILES := affichage.c main.c backwards.c forward.c save.c traitement.c
OBJFILES := $(patsubst %.c, $(BUILDDIR)/%.o, $(SRCFILES))

all: $(BUILDDIR) libisentlib.a affichage

$(BUILDDIR):
	mkdir $(BUILDDIR)

libisentlib.a:
	make -C gfxlib/

affichage: $(OBJFILES)
	$(CC) $(CFLAGS) $@ $^ gfxlib/build/libisentlib.a -lm -lglut -lGL -lX11 -pthread

$(BUILDDIR)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $@ -c $< -Wno-unused-result

clean:
	make clean -C gfxlib/
	rm -f $(BUILDDIR)/*.o
	rm -fr $(BUILDDIR)
	rm -f affichage
