/**
 * @file qsort.c
 * @author volovo
 * @date 11.12.2014
 * @brief implementace quick sortu
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "qsort.h"

static void swap(void *a, void *b, int size) {
	char *tp;
	tp = malloc(size);
	assert(tp != NULL);
	memcpy(tp, a, size);
	memcpy(a, b, size);
	memcpy(b, tp, size);
	free(tp);
}

void mqsort(void *base, int size, int elem_size, int (*cmpfn)(void *, void *)) {
	char *current, *right_elem;
	int new_front_size = 0;

	current  = (char *)base + elem_size;                 //pick the second element
	right_elem = (char *)base + (size - 1) * elem_size;  //pick the last element

	while (current <= right_elem) {
		if (cmpfn(current, base) < 0) {
			new_front_size++;
			swap(current, (char *)base + (new_front_size * elem_size), elem_size);
		}
		current = current + elem_size;                   //get next element
	}
	swap(base, (char *)base + (new_front_size * elem_size), elem_size);

	if (new_front_size > 1) 
		mqsort(base, new_front_size, elem_size, cmpfn);
	if (size - new_front_size - 1 > 0)
		mqsort((char *)base + ((new_front_size + 1) * elem_size), size - new_front_size - 1, elem_size, cmpfn);
}

