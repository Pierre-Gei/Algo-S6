CC := gcc
CFLAGS := -Wall -O2 -o

BUILDDIR := ./build
INCLUDE := ./include
SRC := ./src
SRCFILES := main.c affichage.c backwards.c forward.c save.c traitement.c
OBJFILES := $(patsubst %.c, $(BUILDDIR)/%.o, $(SRCFILES))

all: $(BUILDDIR) libisentlib.a main

$(BUILDDIR):
	mkdir $(BUILDDIR)

libisentlib.a:
	make -C gfxlib/

main: $(OBJFILES)
	$(CC) $(CFLAGS) $@ $^ gfxlib/build/libisentlib.a -lm -lglut -lGL -lX11 -pthread

$(BUILDDIR)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $@ -c $< -Wno-unused-result

clean:
	make clean -C gfxlib/
	rm -f $(BUILDDIR)/*.o
	rm -fr $(BUILDDIR)
	rm -f main
