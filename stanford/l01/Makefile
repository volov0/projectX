#
# Basic Makefile
#

CC=g++
CFLAGS=-c -Wall -ansi -pedantic-errors

 
all: assign

assign: assign.o
		$(CC) assign.o -o assign

assign.o: assign.cpp
		$(CC) $(CFLAGS) assign.cpp

clean:
		rm -rf *o hello
        
