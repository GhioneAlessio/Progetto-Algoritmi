CC=gcc
CFLAGS= -O3 -g -Wall
#---Directories---
SRCDIR = ./src
MODDIR = ./modules
BUILDDIR = ./build
BINDIR = ./bin
#---
OBJS := skiplist.o 

$(BINDIR)/main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/main.c $(BUILDDIR)/$(OBJS)

%.o : $(MODDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

run:
	cd bin/ && ./main ../dictionary.txt ../correctme.txt
clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/*