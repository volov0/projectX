/**
 * @file rotate.c
 * @author volovo
 * @date 16.12.2014
 * @brief implementace rotace
 */

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "rotate.h"

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

