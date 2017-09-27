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

CFILES=src/main.c src/functions.c src/table.c src/tree.c

# include directoryy
IDIR=include/

# header files
IFILES=$(IDIR)defs.h \
       $(IDIR)tree.h \
       $(IDIR)functions.h \
       $(IDIR)tree.h

# executable name
EXEC_NAME_REL=prefix_tree
EXEC_NAME_DBG=prefix_tree_dbg

# default test file
DEFAULT_TEST_FILE=test_files/tabela_enunciado.txt

run: all
	bin/release/$(EXEC_NAME_REL)  $(DEFAULT_TEST_FILE)

run_dbg: all
	bin/debug/$(EXEC_NAME_DBG)  $(DEFAULT_TEST_FILE)

all: prefix_tree prefix_tree_dbg

debug: prefix_tree_dbg

release: prefix_tree

prefix_tree: $(CFILES) $(IFILES)
	$(CC) $(CFLAGS) -I$(IDIR) $(CFILES) -o bin/release/$(EXEC_NAME_REL) 2> build/release/$(EXEC_NAME_REL)_compile.log

prefix_tree_dbg: $(CFILES) $(IFILES)
	$(CC) $(CFLAGSDBG) -I$(IDIR) $(CFILES) -o bin/debug/$(EXEC_NAME_DBG) 2> build/debug/$(EXEC_NAME_DBG)_compile.log


.PHONY: clean
clean:
	rm -f \
    bin/release/* \
    bin/debug/* \
    build/release/* \
    build/debug/*
