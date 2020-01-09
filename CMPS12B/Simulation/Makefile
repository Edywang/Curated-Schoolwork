#------------------------------------------------------------------------------
# Edwin Wang, ekwang, 12B, April 30th 2019, pa3, Makefile, Makefile, % make <all, clean, submit, or no arg>
#------------------------------------------------------------------------------
ASSGNAME = pa4
MAINCLASS  = Simulation
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 
SUBMIT = submit cmps012b-pt.s19 $(ASSGNAME)

all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)

check:
	ls /afs/cats.ucsc.edu/class/cmps012b-pt.s19/$(ASSGNAME)/ekwang
	
submit: $(SOURCES)
	$(SUBMIT) $(SOURCES)