# compiler
CC=gcc

# compiler flags for main program (release)
CFLAGS=-Wall \
       -Wextra \
       -O2 \

# compiler flags for main program (debug)
CFLAGSDBG=-Wall \
          -Wextra \
          -g \
		  -fno-omit-frame-pointer \
		  -fsanitize=address \
		  -fsanitize=leak \
		  -fsanitize=undefined \

IDIR=include/

IFILES=$(IDIR)defs.h \
       $(IDIR)tree.h

all: prefix_tree prefix_tree_dbg

debug: prefix_tree_dbg

release: prefix_tree

prefix_tree: src/main.c src/tree.c $(IFILES)
	$(CC) $(CFLAGS) -I$(IDIR) src/main.c src/tree.c -o bin/release/prefix_tree 2> build/release/tree_compile.log

prefix_tree_dbg: src/main.c src/tree.c $(IFILES)
	$(CC) $(CFLAGSDBG) -I$(IDIR) src/main.c src/tree.c -o bin/debug/prefix_tree_dbg 2> build/debug/tree_compile_dbg.log


.PHONY: clean
clean:
	rm -f \
    bin/release/* \
    bin/debug/* \
    build/release/* \
    build/debug/*
