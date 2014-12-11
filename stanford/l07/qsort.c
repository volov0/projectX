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
	if (size == 1) return;
	if (size == 2) {
		if (cmpfn(base, (char *)base + elem_size) < 0) {
			rotate(base, (char *)base + elem_size, (char *)base + 2*elem_size);
		}
	}
	else {
		int front_size = size / 2;
		mqsort(base, front_size, elem_size, cmpfn);
		mqsort((char *)base + front_size*elem_size, size - front_size, elem_size, cmpfn);
	}
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

