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

void mqsort(void *base, int size, int elem_size, int (*cmpfn)(void *, void *)) {
	int i;
	for (i = 0; i < size; i++) printf("%d ", ((int *)base)[i]);
	printf("\n");

	void *pivot_elem, *left_elem, *right_elem;
	
	left_elem  = base;
	right_elem = (char *)base + (size - 1) * elem_size;
	pivot_elem = (char *)base + elem_size * size / 2;

	do  {
		while ((cmpfn(left_elem, pivot_elem) < 0) && (left_elem < right_elem)) {
			left_elem = (char *)left_elem + elem_size;
		}
		while ((cmpfn(right_elem, pivot_elem) > 0) && (right_elem < left_elem)) {
			right_elem = (char *)right_elem - elem_size;
		}

		if (left_elem <= right_elem) {
			rotate(left_elem, right_elem, (char *)right_elem + elem_size);
			left_elem = (char *)left_elem + elem_size;
			right_elem = (char *)right_elem - elem_size;
		}
	} while (left_elem < right_elem);

	int front_size = ((char *)right_elem - (char *)base) / elem_size;

	if (right_elem > base) 
		mqsort(base, front_size, elem_size, cmpfn);
	if ((char *)left_elem < (char *)base + elem_size * (size - 1))
		mqsort(left_elem, size - front_size, elem_size, cmpfn);
}

void rotate(void *front, void *middle, void *end) {
	void *temp;
	void *end_start;
	int front_size, end_size;

	front_size = (char *)middle - (char *)front;
	end_size   = (char *)end - (char *)middle;
	assert((front_size > 0) && (end_size > 0));

	temp = malloc(front_size);
	end_start = (char *)end - ((char *)middle - (char *)front);

	/* memcpy nelze pouzit na kopirovani bloku, ktere se prekryvaji
	 * memcpy se snazi byt co nejefektivnejsi -> zadna kontrola vstupu
	 * musi se pouzit memmove */
	memcpy(temp, front, front_size);
	memmove(front, middle, end_size);
	memcpy(end_start, temp, front_size);
} 

