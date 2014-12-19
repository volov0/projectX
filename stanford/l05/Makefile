#
# Basic Makefile
#

CC=gcc
CPP=g++
CFLAGS=-c -g -Wall # -ansi -pedantic-errors

 
all: generic_search cpp_search

generic_search: generic_search.o
		$(CC) generic_search.o -o generic_search

generic_search.o: generic_search.c 
		$(CC) $(CFLAGS) generic_search.c

cpp_search: cpp_search.o 
		$(CPP) cpp_search.o -o cpp_search

cpp_search.o: cpp_search.cpp tsearch.hpp 
		$(CPP) $(CFLAGS) cpp_search.cpp

clean:
		rm -rf *o generic_search cpp_search
        
