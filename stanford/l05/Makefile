#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -ansi -pedantic-errors

 
all: generic_search

generic_search: generic_search.o
		$(CC) generic_search.o -o generic_search

generic_search.o: generic_search.c 
		$(CC) $(CFLAGS) generic_search.c

clean:
		rm -rf *o generic_search
        
