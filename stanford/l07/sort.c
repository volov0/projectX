/**
 * @file sort.c
 * @author volovo
 * @date 11.12.2014
 * @brief implementace funkce sortovani
 */

#include <stdio.h>
#include <stdlib.h>
#include "qsort.h"

int int_cmp(void *a, void *b) {
	int *ia = (int *)a;
	int *ib = (int *)b;
	return (*ia - *ib);
}
/**
 * Function main
 * -------------
 * - test 01 - qsort
 */
int main(int argc, char *argv[]) {
	/* test 01 - quick sort */
	int arr[10];
	int i;

	printf("  --- TEST 01 ---\n");
	for (i = 0; i < 10; i++) {
		arr[i] = random() % 100;
		printf("%d ", arr[i]);
	}
	printf("\n");

	qsort(&arr, 10, sizeof(int), int_cmp);

	for (i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}

