
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall 
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: dbug hack01 hack02 hack03 

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

hack03: hack03.o  
		$(CC) hack03.o -o hack03

hack03.o: hack03.c  
		$(CC) $(CFLAGS) hack03.c

clean:
		rm -rf *o dbug
