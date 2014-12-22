/**
 * @file dump.c
 * @author volovo
 * @date 19.12.2014
 * @brief Hexadecimal memory dump
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "dump.h"
#include "../headers/colors.h"

void dump(void *addr, int len) {
	int i, j;                                        
	//printf("    dumping 0x%lx-----\n", (long)addr);
	printf("%s0x%016lx%s ", KCYN, (long)addr, KNRM);
	for (i = 0; i < len; i++) {                      
		printf("%02x",(unsigned char)((char *)addr)[i]);              
		if ((i + 1) % 4 == 0) printf(" ");                                 
		if ((i + 1) % 16 == 0) {                       
			printf("    *");                             
			for (j = 0; j < 16; j++) {                  
				if (isprint(((char *)addr)[i-15+j])) printf("%c",((char *)addr)[i-15+j]);
				else printf(".");
			}                                            
			printf("*\n");                           
			if (i + 1 < len) {
				printf("%s0x%016lx%s ", KCYN, (long)addr + i + 1, KNRM);
			}
		}                                              
	}                                                
	printf("-----------------------------------\n"); 
}

static void dump_range(void *addr_from, void *addr_to) {
	int l = (char *)addr_to - (char *)addr_from;
	assert(l > 0);
	dump(addr_from, l);
}

void dump_stack(int depth) {
	void *actual_bp, *actual_ip;           // registr ve funkci dump_stack - ty me nezajimaji...
	void *previous_bp;                     //  ... me zajimaji ty predesle 
	int i;

	// kdyz kompilator neni gcc - warning
	#ifndef __GNUC__
		fprintf(stderr, "Warning compilator was not GCC. There may be some inconsistence.\n");
	#endif
	asm("movq %%rbp, %0;" : "=r" (actual_bp) : );
	for (i = 0; i < depth; i++) {
		/* base pointeru predchozi funkce je ulozen tesne za rbp */
	  	memcpy(&previous_bp, actual_bp, sizeof(void *));  
		  
		/* instruction pointer je ulozen 8/4bytu za rbp */
	  	memcpy(&actual_ip, (char *)previous_bp + sizeof(void *), sizeof(void *));  

		printf("%sLEVEL %02d function base pointer: %lx%s\n", KGRN, i, (long)previous_bp, KNRM);
		printf("%s         instruction pointer:  %lx%s\n", KYEL, (long)actual_ip, KNRM);
		dump_range(actual_bp, previous_bp);

		/* nastav novy aktualni base pointer - jdu do hloubky */
		memcpy(&actual_bp, &previous_bp, sizeof(void *));        
	}
}
