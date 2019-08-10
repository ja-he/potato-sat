CC := g++
FLAGS := -Wall -Wextra -O3
SRCDIR := src
SRCEXT := cc
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
PROGNAME := potato-sat

all: 
	$(CC) $(FLAGS) $(SOURCES) -o $(PROGNAME)
