/**
 * @file secpower.c
 * @author Vaclav Koudelka
 * @date 19.10.2015
 * @brief funkce ktera zjisti zda csilo na vstupu je mocnina dvou
 */

#include <stdio.h>

/**
 * @param n input number
 * @return 1 if input number n is power of two, 0 otherwise
 */
int secpower(int n) {
	while(1) {
		if (n & 0x1) return 0;
		if (n == 2) return 1;
		n >>= 1;
	}
}

int main(int argc, char **argv) {
	int i = 612;

	if (secpower(i)) 
		printf("Number %d is power of two.\n", i);
	else
		printf("Number %d is not power of two.\n", i);
	
	return 0;
}
