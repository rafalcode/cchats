CC=gcc
CFLAGS0=-g -Wall
CFLAGS=-g -Wall -std=c99
DBGCFLAGS=-g -Wall -DDBG
SPECLIBS=
BZLIBS=-lbz2

EXECUTABLES=wilcrsum wilcsrank

# Wilcoxon rank sum test for indep samples (aka Mann Whitney U)
wilcrsum: wilcrsum.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm

# for dependent (matched pairs "before"/"after" the signed rank is used.
wilcsrank: wilcsrank.c
	${CC} ${DBGCFLAGS} -o $@ $^ -lm

.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
