/**
 * @file c_swap.c
 * @author volovo
 * @date 19.12.2014
 * @brief jednoduchy swap, cil je ukazat rozdil mezi pointerem
 *    a c++ referenci ve strojovem kodu
 */

#include <stdio.h>

void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main(int argc, char *argv[]) {
	int x, y;
	x = 10;
	y = 20;
	printf("x = %d, y = %d\nswap\n", x, y);
	swap(&x, &y);
	printf("x = %d, y = %d\n", x, y);
	return 0;
}
