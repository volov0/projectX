/**
 * @file dump.c
 * @author volovo
 * @date 19.12.2014
 * @brief Hexadecimal memory dump
 */

#include <stdio.h>
#include <assert.h>
#include "dump.h"

void dump(void *addr, int len) {
	int i, j;                                        
	printf("--- dumping 0x%lx-----\n    ", (long)addr);
	for (i = 0; i < len; i++) {                      
		printf("%02x",(unsigned char)((char *)addr)[i]);              
		if ((i + 1) % 4 == 0) printf(" ");                                 
		if ((i + 1) % 16 == 0) {                       
			printf("    *");                             
			for (j = 0; j < 16; j++) {                   
				printf("%c",((char *)addr)[i-15+j]);       
			}                                            
			printf("*\n    ");                           
		}                                              
	}                                                
	printf("-----------------------------------\n"); 
}

void static dump_range(void *addr_from, void *addr_to) {
	int l = (char *)addr_to - (char *)addr_from;
	assert(l > 0);
	dump(addr_from, l);
}

void dump_stack(int depth) {
	void *bp_value, *sp_value;
	asm("movq %%rbp, %0;" : "=r" (bp_value) : );
	asm("movq %%rsp, %0;" : "=r" (sp_value) : );
	/* vem rbp + 8, coz by melo byt predchozi rbp a dumpuj od predchoziho rbp do aktualniho rbp */
	// kdyz kompilator neni gcc - warning
	printf("BASE: %lx; STACK: %lx\n", (long)bp_value, (long)sp_value);
	//dump_range(sp_value, bp_value);
	dump_range(sp_value, (char *)bp_value + 8);
}
