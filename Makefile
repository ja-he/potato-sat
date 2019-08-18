CC := clang++
FLAGS := -Wall -Wextra -Wpedantic -O3 -std=c++2a
SRCEXT := cc
SRCDIR := src
TESTDIR := test
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT) ! -name main.$(SRCEXT))
MAINFILE := $(SRCDIR)/main.$(SRCEXT)
TESTFILE := $(TESTDIR)/test.$(SRCEXT)
PROGNAME := bin/potato-sat
TESTPROGNAME := bin/run-tests
CONDITIONALBINDIRCREATION := if [ ! -d bin ]; then mkdir bin; fi 

all: 
	$(CONDITIONALBINDIRCREATION)
	$(CC) $(FLAGS) $(MAINFILE) $(SOURCES) -o $(PROGNAME)

testsuite: 
	$(CONDITIONALBINDIRCREATION)
	$(CC) $(TESTFILE) $(SOURCES) -o $(TESTPROGNAME)

basic: 
	$(CC) $(SOURCES) -o $(PROGNAME)

clean: 
	rm -r bin/*

guidelinescheck: 
	clang-tidy $(SOURCES) --checks=cppcoreguidelines* --

