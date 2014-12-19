
#
# Basic Makefile
#

CC=gcc
CPP=g++
CFLAGS=-c -g -Wall # -ansi -pedantic-errors
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: c_swap cpp_swap

c_swap: c_swap.o  
		$(CC) c_swap.o -o c_swap

c_swap.o: c_swap.c  
		$(CC) $(CFLAGS) c_swap.c
		$(CC) $(SFLAGS) c_swap.c

cpp_swap: cpp_swap.o  
		$(CPP) cpp_swap.o -o cpp_swap

cpp_swap.o: cpp_swap.cpp  
		$(CPP) $(CFLAGS) cpp_swap.cpp
		$(CPP) $(SFLAGS) cpp_swap.cpp

clean:
		rm -rf *o c_swap cpp_swap
