CC=gcc
CFLAGS= -O3
#---Directories---
SRCDIR = ./src
MODDIR = ./modules
BUILDDIR = ./build
BINDIR = ./bin
#---
OBJS := sort.o

$(BINDIR)/main: $(OBJS)
	$(CC) $(CFLAGS)	-o $@ $(SRCDIR)/main.c $(BUILDDIR)/$(OBJS)
	
%.o : $(MODDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

run:
	cd bin/ && ./main ../records2.csv out.dump quicksort 1 2  && cd ..

clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/*