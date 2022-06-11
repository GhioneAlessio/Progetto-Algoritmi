CC=gcc
CFLAGS= -O3 -g -Wall
#---Directories---
SRCDIR = ./src
MODDIR = ./modules
BUILDDIR = ./build
BINDIR = ./bin
dir_guard = @mkdir -p $(BINDIR) $(BUILDDIR)
#---
OBJS := skiplist.o
OBJS_TEST := unity.o

%.o : $(MODDIR)/%.c
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

$(BINDIR)/main_ex2: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/main_ex2.c $(BUILDDIR)/$(OBJS)

$(BINDIR)/skiplist_tests: $(OBJS_TEST)
	$(CC) $(CFLAGS)	-o $@ $(SRCDIR)/skiplist_tests.c $(BUILDDIR)/$(OBJS) $(BUILDDIR)/$(OBJS_TEST)

run:
	cd bin/ && ./main_ex2 ../dictionary.txt ../correctme.txt

test: $(BINDIR)/main_ex2 $(BINDIR)/skiplist_tests
	cd bin/ && ./skiplist_tests && cd ..

clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/*

val: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log bin/main_ex2 dictionary.txt correctme.txt

val_test: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log bin/skiplist_tests