CC=gcc
CFLAGS= -O3
#---Directories---
SRCDIR = ./src
MODDIR = ./modules
BUILDDIR = ./build
BINDIR = ./bin
#---
OBJS := skiplist.o 

$(BINDIR)/main: $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/main.c $(BUILDDIR)/$(OBJS)

%.o : $(MODDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

run:
	cd bin/ && ./main ../dictionary.txt
clean: 
	rm -f $(BUILDDIR)/* $(BINDIR)/*