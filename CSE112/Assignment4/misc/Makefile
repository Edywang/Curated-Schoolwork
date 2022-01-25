# $Id: Makefile,v 1.5 2020-11-26 15:48:50-08 - - $

TARGETS = err0 err1 errn abrt seg zero foo invalid
SUBMAKE = make --no-print-directory

all :
	for target in ${TARGETS}; do \
	   echo make $$target:; \
	   ${SUBMAKE} $$target; \
	done

err0 :
	error 0

err1 :
	error 1

errn :
	error -1

abrt :
	abort

seg :
	segfault

zero :
	zerodivide

foo :
	foo bar baz
