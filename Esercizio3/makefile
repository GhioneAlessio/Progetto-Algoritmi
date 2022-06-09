JFLAGS = -d
JC = javac
#---Directories---
SRCDIR = ./src
CLASSDIR = ./classes

CLASSES = src/Main_ex3.java 

.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $(CLASSDIR) $*.java 

default: classes

classes: $(CLASSES:.java=.class)

run: 
	cd $(CLASSDIR)/ && java src.MainEx3

clean:
	rm -r -f $(CLASSDIR)/* 