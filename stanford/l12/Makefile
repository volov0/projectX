
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -ansi -pedantic-errors
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: preproc

preproc: preproc.o  
		$(CC) preproc.o -o preproc

preproc.o: preproc.c preproc.h 
		$(CC) $(CFLAGS) preproc.c

clean:
		rm -rf *o preproc
