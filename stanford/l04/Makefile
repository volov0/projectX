#
# Basic Makefile
#

CC=g++
#CFLAGS=-c -g -Wall -ansi -pedantic-errors
CFLAGS=-c -g 

 
all: pointers

pointers: pointers.o
		$(CC) pointers.o -o pointers

pointers.o: pointers.cpp ../headers/mydefs.h
		$(CC) $(CFLAGS) pointers.cpp

clean:
		rm -rf *o pointers
        
