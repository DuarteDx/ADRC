# compiler
CC = gcc

# compiler flags for main program (release)
CFLAGS = -Wall \
         -Wextra \
         -O2 \

# compiler flags for main program (debug with sanitizers)
CFLAGSDBG_1 = -Wall \
              -Wextra \
              -g \
              -fno-omit-frame-pointer \
              -fsanitize=leak \
              -fsanitize=address \
              -fsanitize=undefined \

# compiler flags for main program (debug with valgrind/ddd)
CFLAGSDBG_2 = -Wall \
              -Wextra \
              -g \
              -fno-omit-frame-pointer \

CFILES = src/main.c \
         src/functions.c\
         src/table.c\
         src/tree.c\
         src/tree2.c

# include directoryy
IDIR = include/

# header files
IFILES = $(IDIR)defs.h \
         $(IDIR)tree.h \
         $(IDIR)functions.h \
         $(IDIR)tree.h \
         $(IDIR)tree2.h

# executable name
EXEC_NAME_REL = prefix_tree
EXEC_NAME_DBG_1 = prefix_tree_dbg_1
EXEC_NAME_DBG_2 = prefix_tree_dbg_2

# default test file
DEFAULT_TEST_FILE = test_files/testfile2.txt

run: all
	@echo "\n>>>>>>>>>> EXECUTING RELEASE TARGET. EXECUTION COMMAND:"
	bin/release/$(EXEC_NAME_REL)  $(DEFAULT_TEST_FILE)

run_sanitize: all
	@echo "\n>>>>>>>>>> DEBUGGING WITH SANITIZERS. EXECUTION COMMAND:"
	bin/debug1/$(EXEC_NAME_DBG_1)  $(DEFAULT_TEST_FILE)

run_valgrind: all
	@echo "\n>>>>>>>>>> DEBUGGING WITH VALGRIND. EXECUTION COMMAND:"
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_output.val bin/debug2/$(EXEC_NAME_DBG_2)  $(DEFAULT_TEST_FILE)

run_ddd: all
	@echo "\n>>>>>>>>>> DEBUGGING WITH DDD. EXECUTION COMMAND:"
	ddd --args bin/debug2/$(EXEC_NAME_DBG_2) $(DEFAULT_TEST_FILE)

all: prefix_tree prefix_tree_dbg_1 prefix_tree_dbg_2
	@echo "\n>>>>>>>>>> PATHS FOR TEST FILES:"
	@realpath test_files/*

debug1: prefix_tree_dbg_1

debug2: prefix_tree_dbg_2

release: prefix_tree

prefix_tree: $(CFILES) $(IFILES) directory_structure
	@echo "\n>>>>>>>>>> COMPILING RELEASE TARGET"
	$(CC) $(CFLAGS) -I$(IDIR) $(CFILES) -o bin/release/$(EXEC_NAME_REL) 2> build/release/$(EXEC_NAME_REL)_compile.log

prefix_tree_dbg_1: $(CFILES) $(IFILES) directory_structure
	@echo "\n>>>>>>>>>> COMPILING DEBUG TARGET 1 FOR USE WITH SANITIZERS"
	$(CC) $(CFLAGSDBG_1) -I$(IDIR) $(CFILES) -o bin/debug1/$(EXEC_NAME_DBG_1) 2> build/debug1/$(EXEC_NAME_DBG_1)_compile.log

prefix_tree_dbg_2: $(CFILES) $(IFILES) directory_structure
	@echo "\n>>>>>>>>>> COMPILING DEBUG TARGET 2 FOR USE WITH VALGRIND/DDD"
	$(CC) $(CFLAGSDBG_2) -I$(IDIR) $(CFILES) -o bin/debug2/$(EXEC_NAME_DBG_2) 2> build/debug2/$(EXEC_NAME_DBG_2)_compile.log

.PHONY: directory_structure
directory_structure:
	@echo "\n>>>>>>>>>> CREATING BUILD ENVIRONMENT"
	mkdir -p ./bin/debug1 ./bin/debug2 ./bin/release ./build/debug1 ./build/debug2 ./build/release

.PHONY: clean
clean:
	rm -f \
    bin/release/* \
    bin/debug1/* \
    bin/debug2/* \
    build/release/* \
    build/debug1/* \
    build/debug2/*
