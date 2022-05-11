CC=gcc
CFLAGS= -O3 -g -Wall
#---Directories---
SRCDIR = ./src
MODDIR = ./modules
BUILDDIR = ./build
BINDIR = ./bin
#---
OBJS := skiplist.o 

$(BINDIR)/main_ex2: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/main_ex2.c $(BUILDDIR)/$(OBJS)

%.o : $(MODDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

run:
	cd bin/ && ./main_ex2 ../dictionary.txt ../correctme.txt
clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/*

val: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log bin/main dictionary.txt correctme.txt