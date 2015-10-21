#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -ansi -pedantic-errors

all: generic_queue.a sample

generic_queue.a: generic_queue.o
	ar rc libgeneric_queue.a *.o

generic_queue.o: generic_queue.c generic_queue.h
	$(CC) $(CFLAGS) generic_queue.c

sample: sample.o generic_queue.o
	$(CC) sample.o generic_queue.o -o sample

sample.o: sample.c
	$(CC) $(CFLAGS) sample.c

clean:
	rm -rf *o *a 

