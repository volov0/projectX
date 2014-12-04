/**
 * @file int_stack.c
 * @author volovo
 * @date 1.12.2014
 * @brief integer stack implementace funkci
 */

#include "int_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void int_stack_new(int_stack *s) {
	s->logical_length = 0;
	s->allocated_length = STACK_INIT_SIZE;
	s->elem = (int *)malloc(STACK_INIT_SIZE*sizeof(int));
	assert(s->elem != NULL);
}

void int_stack_dispose(int_stack *s) {
	free(s->elem);
	s->logical_length = 0;
	s->allocated_length = 0;
}

void int_stack_push(int_stack *s, int value) {
	if (s->logical_length == s->allocated_length) {
		s->allocated_length *= 2;
		s->elem = (int *)realloc(s->elem, s->allocated_length*sizeof(int));
		assert(s->elem != NULL);
	}
	s->elem[s->logical_length] = value;
	s->logical_length++;
}

int int_stack_pop(int_stack *s) {
	assert(s->logical_length > 0);
	s->logical_length--;
	return s->elem[s->logical_length];
}

void int_stack_print(int_stack *s) {
	int i;
	for (i = 0; i < s->logical_length; i++) {
		printf("%d ", s->elem[i]);
	}
	printf("\n");
}
