#
# Basic Makefile
#

CPP=g++
CFLAGS=-c -g -Wall -std=c++11 #-ansi -pedantic-errors

all: cond_var

cond_var: cond_var.o
	$(CPP) -pthread cond_var.o -o cond_var

cond_var.o: cond_var.cpp
	$(CPP) $(CFLAGS) cond_var.cpp -o cond_var.o

clean:
	rm -rf *.o cond_var
