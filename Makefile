CC := clang++
FLAGS := -Wall -Wextra -O3
SRCEXT := cc
SRCDIR := src
TESTDIR := test
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT) ! -name main.$(SRCEXT))
MAINFILE := $(SRCDIR)/main.$(SRCEXT)
TESTFILE := $(TESTDIR)/test.$(SRCEXT)
PROGNAME := bin/potato-sat
TESTPROGNAME := bin/run-tests

all: 
	$(CC) $(FLAGS) $(MAINFILE) $(SOURCES) -o $(PROGNAME)

testsuite: 
	$(CC) $(TESTFILE) $(SOURCES) -o $(TESTPROGNAME)

basic: 
	$(CC) $(SOURCES) -o $(PROGNAME)

clean: 
	rm -r bin/*
