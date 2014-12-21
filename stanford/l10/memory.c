/**
 * @file memory.c
 * @author volovo
 * @date 19.12.2014
 * @brief ukazuje dumpovani pameti, stacku, atd.
 */

#include <stdio.h>
#include "dump.h"

/**
 * Function factorial
 * ------------------
 * @brief faktorial
 */
int factorial(int n) {
	int i;
	dump_stack(5);
	if (n == 1)	{ /*dump_stack(5);*/ return 1; }
	return n * factorial(n - 1);
}

/**
 * Function main
 * -------------
 * -dumpovani stacku a podobne
 */
int main(int argc, char *argv[]) {
	int i = 0xaaabbb;
	void *bp_value, *sp_value;
	asm("movq %%rbp, %0;" : "=r" (bp_value) : );
	asm("movq %%rsp, %0;" : "=r" (sp_value) : );
	printf("%lx\n", (long)bp_value);
	printf("%lx\n", (long)sp_value);
	dump(bp_value, 64);
	dump(sp_value, 64);
	dump((void *)(unsigned long)sp_value - 64, 64);
	factorial(5);
	return 0;
}
