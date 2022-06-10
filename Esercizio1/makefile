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
	cd bin/ && ./main ../records.csv out.dump quicksort 1  && cd ..

test: $(BINDIR)/main $(BINDIR)/sort_tests
	cd bin/ && ./sort_tests && cd ..

val: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log bin/main records.csv out.dump quicksort 3 

val_test: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log bin/sort_tests

clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/*