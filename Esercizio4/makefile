JFLAGS = -d
JC = javac
#---Directories---
SRCDIR = ./src
CLASSDIR = ./classes

CLASSES = src/Dist.java src/Main_ex4.java

.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $(CLASSDIR) $*.java 

default: classes

classes: $(CLASSES:.java=.class)

run: 
	cd $(CLASSDIR)/ && java src.Main_ex4 ../italian_dist_graph.csv

clean:
	rm -r -f $(CLASSDIR)/* 