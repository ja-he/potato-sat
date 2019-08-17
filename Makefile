CC := g++
FLAGS := -Wall -Wextra -O3
SOURCES := src/dpll-basic.cc
MAIN := src/main.cc
TESTFILE := test/test.cc
PROGNAME := bin/potato-sat
TESTPROGNAME := bin/run-tests

all: 
	$(CC) $(FLAGS) $(MAIN) $(SOURCES) -o $(PROGNAME)

testsuite: 
	$(CC) $(TESTFILE) $(SOURCES) -o $(TESTPROGNAME)

basic: 
	$(CC) $(SOURCES) -o $(PROGNAME)
