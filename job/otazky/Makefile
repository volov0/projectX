#
# Basic Makefile
#
TARGETS  = secpower revstr
CC       = gcc
CFLAGS   = -c -g -Wall #-ansi -pedantic-errors
#SOURCES  := rxml.cpp xmlprocessor.cpp
#INCLUDES := xmlprocessor.h
#OBJECTS  := $(SOURCES:.cpp=*.o)
#OURCES  := $(TARGETS:=.c)
SOURCES  := $(wildcard *.c)
OBJECTS  := $(notdir $(SOURCES:.c=.o))
TARGETS  := $(notdir $(SOURCES:.c=))
#$(TARGETS:=.o)

#SOURCES  := $(wildcard *.cpp)
#INCLUDES := $(wildcard *.hpp)
#OBJECTS  := $(SOURCES:.cpp=*.o)

all: revstr secpower logshift
	@echo ...compilation done...

revstr: revstr.o
	$(CC) $(OFLAGS) revstr.o -o revstr

secpower: secpower.o
	$(CC) $(OFLAGS) secpower.o -o secpower

logshift: logshift.o
	$(CC) $(OFLAGS) logshift.o -o logshift

#    $@ ... leva strana :
#    $^ ... prava strana :  (zavislosti)
#    $< ... prvni polozka zavislosti
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

#(TARGETS): $(OBJECTS)
#$(CC) $(OFLAGS) $(OBJECTS) -o $(TARGETS)

#$(OBJECTS): $(SOURCES) 
#		$(CC) $(CFLAGS) $(SOURCES)

#$(foreach tar,$(TARGETS),echo $(tar))
clean:
		rm -rf *o $(TARGETS) 
        
