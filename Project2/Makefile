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
              -pg \
              -fno-omit-frame-pointer \
              -fsanitize=leak \
              -fsanitize=address \
              -fsanitize=undefined \

# compiler flags for main program (debug with valgrind/ddd)
CFLAGSDBG_2 = -Wall \
              -Wextra \
              -g \
              -fno-omit-frame-pointer \

CFILES = src/*

# include directoryy
IDIR = include/

# header files
IFILES = $(IDIR)*

# executable name
EXEC_NAME_REL = inter_domain_routing
EXEC_NAME_DBG_1 = inter_domain_routing_dbg_1
EXEC_NAME_DBG_2 = inter_domain_routing_dbg_2

# default test file
DEFAULT_TEST_FILE = test_files/SmallNetwork.txt

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

all: inter_domain_routing inter_domain_routing_dbg_1 inter_domain_routing_dbg_2
	@echo "\n>>>>>>>>>> PATHS FOR TEST FILES:"
	@realpath test_files/*

debug1: inter_domain_routing_dbg_1

debug2: inter_domain_routing_dbg_2

release: inter_domain_routing

inter_domain_routing: $(CFILES) $(IFILES) directory_structure
	@echo "\n>>>>>>>>>> COMPILING RELEASE TARGET"
	$(CC) $(CFLAGS) -I$(IDIR) $(CFILES) -o bin/release/$(EXEC_NAME_REL) 2> build/release/$(EXEC_NAME_REL)_compile.log

inter_domain_routing_dbg_1: $(CFILES) $(IFILES) directory_structure
	@echo "\n>>>>>>>>>> COMPILING DEBUG TARGET 1 FOR USE WITH SANITIZERS"
	$(CC) $(CFLAGSDBG_1) -I$(IDIR) $(CFILES) -o bin/debug1/$(EXEC_NAME_DBG_1) 2> build/debug1/$(EXEC_NAME_DBG_1)_compile.log

inter_domain_routing_dbg_2: $(CFILES) $(IFILES) directory_structure
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
