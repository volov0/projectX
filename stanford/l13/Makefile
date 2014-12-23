
#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -c rika - udelaj jenom kompilaci = vygeneruj .o soubor
SFLAGS=-S -O0 -fno-asynchronous-unwind-tables

 
all: link weird weird2

link: link.o  
		$(CC) link.o -o link

link.o: link.c  
		$(CC) $(CFLAGS) link.c
#		$(CC) -E link.c    # vygeneruje vystup preprocesoru

weird: weird.o  
		$(CC) weird.o -o weird

weird.o: weird.c  
		$(CC) $(CFLAGS) weird.c
		
weird2: weird2.o  
		$(CC) weird2.o -o weird2

weird2.o: weird2.c  
		$(CC) $(CFLAGS) weird2.c

clean:
		rm -rf *o link weird weird2
