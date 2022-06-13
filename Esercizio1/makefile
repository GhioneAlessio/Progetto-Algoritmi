CC=gcc
CFLAGS= -O3
#---Directories---
SRCDIR = ./src
MODDIR = ./modules
BUILDDIR = ./build
BINDIR = ./bin
dir_guard = @mkdir -p $(BINDIR) $(BUILDDIR)
#---
OBJS := sort.o
OBJS_TEST := unity.o


%.o : $(MODDIR)/%.c
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@
	
$(BINDIR)/main: $(OBJS)
	$(CC) $(CFLAGS)	-o $@ $(SRCDIR)/main.c $(BUILDDIR)/$(OBJS)
	
$(BINDIR)/sort_tests: $(OBJS_TEST)
	$(CC) $(CFLAGS)	-o $@ $(SRCDIR)/sort_tests.c $(BUILDDIR)/$(OBJS) $(BUILDDIR)/$(OBJS_TEST)

all: $(BINDIR)/main $(BINDIR)/sort_tests

run:
	bin/main $(arg1) $(arg2) $(arg3) $(arg4)

test: $(BINDIR)/main $(BINDIR)/sort_tests
	bin/sort_tests

val: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log bin/main $(arg1) $(arg2) $(arg3) $(arg4)

val_test: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log bin/sort_tests

clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/* 