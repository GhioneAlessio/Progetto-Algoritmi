CC=gcc
CFLAGS= -O3
#---Directories---
SRCDIR = ./src
MODDIR = ./modules
BUILDDIR = ./build
BINDIR = ./bin
#---
OBJS := sort.o
OBJS_TEST := sort.o $(BUILDDIR)/unity.o

%.o : $(MODDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@
	
$(BINDIR)/main: $(OBJS)
	$(CC) $(CFLAGS)	-o $@ $(SRCDIR)/main.c $(BUILDDIR)/$(OBJS)
	
$(BINDIR)/sort_tests: $(OBJS_TEST)
	$(CC) $(CFLAGS)	-o $@ $(SRCDIR)/sort_tests.c $(BUILDDIR)/$(OBJS_TEST)

run:
	cd bin/ && ./main ../records.csv out.dump quicksort 1  && cd ..

test: 
	cd bin/ && ./sort_tests && cd ..

clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/*
