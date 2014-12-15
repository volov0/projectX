
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -ansi -pedantic-errors

 
all: sort

sort: sort.o qsort.o 
		$(CC) sort.o qsort.o -o sort

sort.o: sort.c  
		$(CC) $(CFLAGS) sort.c

qsort.o: qsort.c qsort.h
		$(CC) $(CFLAGS) qsort.c
		
clean:
		rm -rf *o sort
