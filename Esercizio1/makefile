CC=gcc
CFLAGS=
#---Directories---
SRCDIR = ./src
MODDIR = ./modules
BUILDDIR = ./build
BINDIR = ./bin
#---
OBJS := quicksort.o

$(BINDIR)/main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/main_qs.c $(BUILDDIR)/$(OBJS)

%.o : $(MODDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@


#quicksort.o:  
#$(CC) $(CFLAGS) -c $(MODDIR)/quicksort.c -o $(BUILDDIR)/quicksort.o

run:
	cd bin/ && ./main ../file_test && cd ..

clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/*
