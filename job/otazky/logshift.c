/**
 * @file logshift.c
 * @author Vaclav Koudelka
 * @date 21.10.2015
 * @brief ukazuje rozdil mezi logickym a aritmetickym shiftem
 */

#include <stdio.h>

/**
 * performs arithmetic shift, because it operates on ints
 * @param n input number
 * @return number of bits in n
 */
int no_of_bits_int(int n) {
	int count;
	while(n) {
		if (n & 0x1) count++;
		n >>= 1;
	}
	return count;
}

/**
 * performs logical shift, because it operates on unsigned ints
 * @param n input number
 * @return number of bits in n
 */
int no_of_bits_unsigned(unsigned int n) {
	int count;
	while(n) {
		if (n & 0x1) count++;
		n >>= 1;
	}
	return count;
}

int main(int argc, char **argv) {
	printf("Number of bits in number %d is %d.\n", 0xFFFFFFFF, no_of_bits_unsigned(0xFFFFFFFF));
	printf("Number of bits in number %d is %d.\n", 0xFFFFFFFF, no_of_bits_int(0xFFFFFFFF)); // loops indefinitely
	
	return 0;
}
