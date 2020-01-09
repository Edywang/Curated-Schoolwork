#------------------------------------------------------------------------------
#  Makefile for Summer 2019 CS101 PA2
#  Modified by Edwin Wang, ekwang
#  make                     makes Sparse
#  make clean               removes all binaries
#  make memcheck            runs Sparse under valgrind
#------------------------------------------------------------------------------

ASSG           = pa2
CLIENT         = Sparse
ADT1           = Matrix
ADT2           = List
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT1_TEST      = $(ADT1)Test.c
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
ADT2_TEST      = $(ADT2)Test.c
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
SUBMIT         = submit  cmps101-pt.u19 $(ASSG)
CRUZ           = ekwang
CHECK          = ls  /afs/cats.ucsc.edu/class/cmps101-pt.u19/$(ASSG)/$(CRUZ)

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)

submit : $(ADT1_SOURCE) $(ADT2_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER) $(SOURCE) $(ADT1_TEST) $(ADT2_TEST) Makefile README
	$(SUBMIT) $(ADT1_SOURCE) $(ADT2_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER) $(SOURCE) $(ADT1_TEST) $(ADT2_TEST) Makefile README
	
check :
	$(CHECK)