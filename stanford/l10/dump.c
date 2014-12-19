/**
 * @file dump.c
 * @author volovo
 * @date 19.12.2014
 * @brief Hexadecimal memory dump
 */

#include <stdio.h>
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
