#
# Basic Makefile
#

CPP=g++
CFLAGS=-c -g -Wall -std=c++11 #-ansi -pedantic-errors

all: rxml

rxml: rxml.o
	$(CPP) rxml.o -o rxml

rxml.o: rxml.cpp
	$(CPP) $(CFLAGS) rxml.cpp -o rxml.o

clean:
	rm -rf *.o rxml
