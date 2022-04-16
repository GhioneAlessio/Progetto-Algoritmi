CC=gcc
CFLAGS=
#---Directories---
SRCDIR = ./src
MODDIR = ./modules
BUILDDIR = ./build
BINDIR = ./bin
#---
OBJS := sort.o

$(BINDIR)/main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/main.c $(BUILDDIR)/$(OBJS)

%.o : $(MODDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@


#quicksort.o:  
#$(CC) $(CFLAGS) -c $(MODDIR)/quicksort.c -o $(BUILDDIR)/quicksort.o

run:
	cd bin/ && ./main ../records2.csv && cd ..

clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/*
