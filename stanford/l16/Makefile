
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall 
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: prodcons dining 

prodcons: prodcons.o
		$(CC) -pthread prodcons.o -o prodcons

prodcons.o: prodcons.c  
		$(CC) $(CFLAGS) prodcons.c

dining: dining.o
		$(CC) -pthread dining.o -o dining

dining.o: dining.c  
		$(CC) $(CFLAGS) dining.c

clean:
		rm -rf *o dbug
