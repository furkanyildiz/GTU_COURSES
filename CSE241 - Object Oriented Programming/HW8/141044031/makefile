JFLAGS = -g -Xlint
JC = javac
.SUFFIXES: .java .class 
.java.class: 
	$(JC) $(JFLAGS) $*.java

CLASSES = \
        FurkanTemplateLib/FPair.java \
        FurkanTemplateLib/FMap.java  \
        FException.java \
        Bigram.java \
        BigramMap.java \
        BigramDyn.java \
        _mainTester.java 

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
	$(RM) FurkanTemplateLib/*.class