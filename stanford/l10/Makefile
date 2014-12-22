
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -W #all # -ansi -pedantic-errors
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: memory

memory: memory.o dump.o 
		$(CC) memory.o dump.o -o memory

memory.o: memory.c  
		$(CC) $(CFLAGS) memory.c
		$(CC) $(SFLAGS) memory.c

dump.o: dump.c dump.h
		$(CC) $(CFLAGS) dump.c
		$(CC) $(SFLAGS) dump.c

clean:
		rm -rf *o memory
