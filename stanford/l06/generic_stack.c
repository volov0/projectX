/**
 * @file generic_stack.c
 * @author volovo
 * @date 1.12.2041
 * @brief Generic stack implementace
 */

#include "generic_stack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void stack_new(stack *s, int elem_size, void (*cpyfn)(void *, void *)) {
	s->elem_size = elem_size;
	s->cpyfn = cpyfn;
	s->logical_length = 0;
	s->allocated_length = STACK_INIT_SIZE;
	s->elem = malloc(STACK_INIT_SIZE * s->elem_size);
	assert(s->elem != NULL);
}

void stack_dispose(stack *s) {
	free(s->elem);
}

void stack_push(stack *s, void *value) {
	if (s->logical_length == s->allocated_length) {
		s->allocated_length *= 2;
		s->elem = realloc(s->elem, s->allocated_length * s->elem_size);
		assert(s->elem != NULL);
	}
	/* V nasledujicim copy funkci musim pretypovat s->elem na (void*) jinak si
	   kompilator bude myslet, ze s->elem je (void**) a tim padem ma
	   velikost 8bytu na 64bitovy masine a dela spatne pointer aritmetiku */
	//memcpy(((void *)s->elem) + (s->logical_length++ * s->elem_size), value, s->elem_size); 
	s->cpyfn(((void *)s->elem) + (s->logical_length++ * s->elem_size), value);
}

void *stack_pop(stack *s) {
	/* opet musim udelat pretypovani na (void*) kvuli pointer aritmetice */
	return ((void *)s->elem) + (--s->logical_length * s->elem_size);
}

