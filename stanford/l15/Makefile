
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall 
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: threads 

threads: threads.o
		$(CC) -pthread threads.o -o threads

threads.o: threads.c  
		$(CC) $(CFLAGS) threads.c

clean:
		rm -rf *o dbug
