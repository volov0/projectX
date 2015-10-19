#
# Basic Makefile
#
TARGETS  = secpower
CC       = gcc
CFLAGS   = -c -g -Wall -ansi -pedantic-errors
#SOURCES  := rxml.cpp xmlprocessor.cpp
#INCLUDES := xmlprocessor.h
#OBJECTS  := $(SOURCES:.cpp=*.o)
SOURCES  := $(TARGETS:=.c)
OBJECTS  := $(TARGETS:=.o)

#SOURCES  := $(wildcard *.cpp)
#INCLUDES := $(wildcard *.hpp)
#OBJECTS  := $(SOURCES:.cpp=*.o)
 
all: $(TARGETS)

$(TARGETS): $(OBJECTS)
		$(CC) $(OFLAGS) $(OBJECTS) -o $(TARGETS)

$(OBJECTS): $(SOURCES) 
		$(CC) $(CFLAGS) $(SOURCES)

clean:
		rm -rf *o $(TARGETS) 
        
