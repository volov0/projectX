
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -ansi -pedantic-errors

 
all: stack

stack: stack.o int_stack.o
		$(CC) stack.o int_stack.o -o stack

stack.o: stack.c 
		$(CC) $(CFLAGS) stack.c
		
int_stack.o: int_stack.c int_stack.h
		$(CC) $(CFLAGS) int_stack.c

clean:
		rm -rf *o stack
