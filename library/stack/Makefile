#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -ansi -pedantic-errors

all: generic_stack.a

generic_stack.a: generic_stack.o
	ar rc libgeneric_stack.a *.o

generic_stack.o: generic_stack.c generic_stack.h
	$(CC) $(CFLAGS) generic_stack.c

clean:
	rm -rf *o *a 

