#
# Basic Makefile
#

CC=gcc
CFLAGS=-c -g -Wall # -ansi -pedantic-errors

 
all: simple

simple: simple.o 
		$(CC) simple.o -o simple

# -S parametr rika, aby se vygeneroval assembler source simple.s
# -O0 parametr udava uroven optimalizace kompilatoru, 0 je nejnizsi a zaroven default
# -fno-asynchronous-unwind-tables - vypne generovani .cfi(Call Frame Information) a .L direktiv
#   - .cfi direktivy GNU assembleru jsou urceny k debugovani a rozmotani stack chainu
#     pokud chybi info o stack pointeru (rsp)
#   - .L jsou lokalni labely
simple.o: simple.c  
		$(CC) $(CFLAGS) simple.c
		$(CC) -S -O0 -fno-asynchronous-unwind-tables simple.c

raw_simple: raw_simple.s
		$(CC) raw_simple.s -o raw_simple
clean:
		rm -rf *o *s simple
