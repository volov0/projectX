#
# Basic Makefile
#

SC=csc

 
all: sum sum_main sum-dynamic 

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

clean:
		rm -rf *o sum
        
