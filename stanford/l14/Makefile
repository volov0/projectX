
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall 
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: dbug hack01 hack02 

dbug: dbug.o  
		$(CC) dbug.o -o dbug

dbug.o: dbug.c  
		$(CC) $(CFLAGS) dbug.c

hack01: hack01.o  
		$(CC) hack01.o -o hack01

hack01.o: hack01.c  
		$(CC) $(CFLAGS) hack01.c

hack02: hack02.o  
		$(CC) hack02.o -o hack02

hack02.o: hack02.c  
		$(CC) $(CFLAGS) hack02.c

clean:
		rm -rf *o dbug
