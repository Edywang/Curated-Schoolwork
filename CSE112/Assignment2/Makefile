# $Id: Makefile,v 1.19 2020-09-06 20:49:42-07 - - $

#
# General useful macros
#

MKFILE     = Makefile
MAKEFLAGS += --no-builtin-rules
DEPFILE    = ${MKFILE}.dep
NOINCLUDE  = ci clean spotless
NEEDINCL   = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
GMAKE      = ${MAKE} --no-print-directory
OCAMLOPT   = ocamlopt -g

#
# File macros
#

EXECBIN    = mbinterp
OBJCMX     = etc.cmx parser.cmx scanner.cmx tables.cmx \
             dumper.cmx interp.cmx main.cmx
OBJCMI     = ${OBJCMX:.cmx=.cmi} absyn.cmi
OBJBIN     = ${OBJCMX:.cmx=.o}
MLSOURCE   = absyn.mli etc.mli etc.ml tables.mli tables.ml \
             dumper.mli dumper.ml interp.mli interp.ml main.ml
GENLEXYACC = parser.mli parser.ml scanner.ml
GENSOURCE  = dumper.mli tables.mli ${GENLEXYACC}
GENFILES   = ${GENSOURCE} parser.output ${DEPFILE}
OTHERFILES = ${MKFILE} ${DEPFILE} using .ocamlinit
ALLSOURCES = ${MLSOURCE} parser.mly scanner.mll ${OTHERFILES}
LISTING    = Listing.ps

#
# General targets
#

all : ${EXECBIN}

${EXECBIN} : ${OBJCMX} ${OBJBIN}
	${OCAMLOPT} str.cmxa ${OBJCMX} -o ${EXECBIN}

%.cmi : %.mli
	${OCAMLOPT} -c $<

%.o %.cmx : %.ml
	${OCAMLOPT} -c $<

%.ml : %.mll
	ocamllex $<

%.mli %.ml : %.mly
	ocamlyacc -v $<


MAKEMLI    = (echo "(* Generated: $$(date) *)"; ${OCAMLOPT} -i $<) >$@

tables.mli : tables.ml absyn.cmi
	${call MAKEMLI}

dumper.mli : dumper.ml absyn.cmi
	${call MAKEMLI}

#
# Misc targets
#

clean :
	- rm ${OBJCMI} ${OBJCMX} ${OBJBIN} ${GENSOURCE}

spotless : clean
	- rm ${EXECBIN} ${GENFILES} ${LISTING} ${LISTING:.ps=.pdf} 

ci : ${ALLSOURCES}
	- checksource ${ALLSOURCES}
	cid -is ${ALLSOURCES}

dep : ${MLSOURCE} ${GENSOURCE}
	@ echo "# Generated: $$(date)" >${DEPFILE}
	ocamldep ${MLSOURCE} ${GENSOURCE} >>${DEPFILE}

${DEPFILE} : tables.mli
	@touch ${DEPFILE}
	${GMAKE} dep

lis : ${ALLSOURCES}
	mkpspdf ${LISTING} ${ALLSOURCES}

again :
	${GMAKE} spotless
	${GMAKE} dep
	${GMAKE} ci
	${GMAKE} all
	${GMAKE} lis

ifeq "${NEEDINCL}" ""
include ${DEPFILE}
endif

