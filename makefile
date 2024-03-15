CFLAGS = -Wall -Wextra -Werror -g

BUILDDIR := ./build
INCLUDE := ./include
SRC := ./src
SRCFILES := affichage.c main.c backwards.c forward.c save.c traitement.c terminal_menu.c
OBJFILES := $(patsubst %.c, $(BUILDDIR)/%.o, $(SRCFILES))

all: $(BUILDDIR) libisentlib.a main

$(BUILDDIR):
	mkdir $(BUILDDIR)

libisentlib.a:
	make -C gfxlib/

main: $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ gfxlib/build/libisentlib.a -lm -lglut -lGL -lX11 -pthread

$(BUILDDIR)/%.o: $(SRC)/%.c $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -Wno-unused-result

clean:
	make clean -C gfxlib/
	rm -f $(BUILDDIR)/*.o
	rm -fr $(BUILDDIR)
	rm -f main