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
 * @detail 
 *   - gcc vzdy alokuje pro lokalni promenna pamet zaokrouhlenou nahoru na 16 bytu,
 *     takze ji celou vyplnim intama i,j,k,l abych to videl
 *   - v dump_stack dostanu nasledujiciL
 *   LEVEL 0 function base pointer: 7fff61ec9cc0
 *   0x00007fff61ec9c90 c09cec61 ff7f0000 a3064000 00000000   prvnich 8bytu je rbp ve fci factorial(da si ji tam fc dump_stack) - zbytek viz $$$$
 *   0x00007fff61ec9ca0 00000000 00000000 236f7373 01000000   posledni 4byty je parametr, zbytek je nejspis rezervovan pro dalsi paramtery
 *   0x00007fff61ec9cb0 dddd0000 cccc0000 bbbb0000 aaaa0a00   lokalni promenne i,j,k,l
 *         $$$ na adrese 0x00007fff61ec9c98 musi byt adresa navratove instrukce ve funkci factorial, ktera se tam ulozila pri instrukci 
 *             CALL dump_stack.
 */
int factorial(int n) {
	int i = 0xaaaaa, j = 0xbbbb, k = 0xcccc, l = 0xdddd;
	if (n == 1)	{ dump_stack(6); return 1; }
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
