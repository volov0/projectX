
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall 
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: prodcons 

prodcons: prodcons.o
		$(CC) -pthread prodcons.o -o prodcons

prodcons.o: prodcons.c  
		$(CC) $(CFLAGS) prodcons.c

clean:
		rm -rf *o dbug
