/**
 * @file memory.c
 * @author volovo
 * @date 19.12.2014
 * @brief ukazuje dumpovani pameti, stacku, atd.
 */

#include <stdio.h>
#include "dump.h"

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
	return 0;
}
