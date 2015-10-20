
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -ansi -pedantic-errors
LIBDIR=../../library/stack
LIBINCL=../../library/stack

 
all: stack

stack: stack.o int_stack.o 
		$(CC) stack.o int_stack.o -o stack -L$(LIBDIR) -lgeneric_stack 

stack.o: stack.c 
		$(CC) $(CFLAGS) -I$(LIBINCL) -L$(LIBDIR) -lgeneric_stack stack.c
		
int_stack.o: int_stack.c int_stack.h
		$(CC) $(CFLAGS) int_stack.c

#generic_stack.o: $(LIBDIR)/generic_stack.c $(LIBDIR)/generic_stack.h
#		$(CC) $(CFLAGS) $(LIBDIR)generic_stack.c

clean:
		rm -rf *o stack *out
