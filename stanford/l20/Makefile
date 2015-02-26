#
# Basic Makefile
#

CC=gcc
SC=csc
CFLAGS=-c -g -Wall # -ansi -pedantic-errors
 

all: sum sum_main sum-dynamic sum-c 

sum: sum.o
		$(SC) sum.o -o sum

sum.o: sum.scm
		$(SC) -c sum.scm

sum_main: sum_main.o
		$(SC) sum_main.o -o sum_main

sum_main.o: sum_main.scm
		$(SC) -c sum_main.scm

sum-dynamic: sum.scm
		$(SC) -dynamic sum.scm

sum-c: sum-c.o
		$(CC)  sum-c.o -o sum-c

sum-c.o: sum-c.c
		$(CC) $(CFLAGS) sum.c -o sum-c.o
		
sum-c.c: sum.scm
		$(SC) -t sum.scm -optimize-level 3 -output-file sum.c

clean:
		rm -rf *o sum
        
