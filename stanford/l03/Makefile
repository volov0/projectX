#
# Basic Makefile
#

CC=g++
CFLAGS=-c -g -Wall -ansi -pedantic-errors

 
all: structs

structs: structs.o
		$(CC) structs.o -o structs

structs.o: structs.cpp ../headers/mydefs.hpp
		$(CC) $(CFLAGS) structs.cpp

clean:
		rm -rf *o structs
        
