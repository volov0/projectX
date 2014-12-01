/**
 * @file generic_stack.c
 * @author volovo
 * @date 1.12.2041
 * @brief Generic stack implementace
 */

#include "generic_stack.h"
#include <stdlib.h>
#include <assert.h>

void stack_new(stack *s, int elem_size) {
	s->elem = malloc(STACK_INIT_SIZE * elem_size);
	assert(s->elem);
	s->elem_size = elem_size;
	s->logical_length = 0;
	s->allocated_length = STACK_INIT_SIZE;
}

void stack_dispose(stack *s) {
	free(s->elem);
}

void stack_push(stack *s, void *value) {
	if (s->logical_length == s->allocated_length) {
		s->allocated_length *= 2;
		s->elem = realloc(s->elem, s->allocated_length * s->elem_size);
		assert(s->elem);
	}
	//s->elem[s->logical_length++]; todo
}

void *stack_pop(stack *s) {
	return s->elem[s->logical_length--];
}

