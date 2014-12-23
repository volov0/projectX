
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -c rika - udelaj jenom kompilaci = vygeneruj .o soubor
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: preproc

preproc: preproc.o  
		$(CC) preproc.o -o preproc

preproc.o: preproc.c preproc.h 
		$(CC) $(CFLAGS) preproc.c
#		$(CC) -E preproc.c    # vygeneruje vystup preprocesoru

clean:
		rm -rf *o preproc
