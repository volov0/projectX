/**
 * @file int_stack.c
 * @author volovo
 * @date 1.12.2014
 * @brief integer stack implementace funkci
 */

#include "int_stack.h"
#include <stdio.h>

void int_stack_new(stack *s) {
}

void int_stack_dispose(stack *s) {
}

void int_stack_push(stack *s, int value) {

}

int int_stack_pop(stack *s) {
	return s->elem[s->logical_lentgh--];
}

void int_stack_print(stack *s, int value) {
	for (int i = 0; i < s->logical_length; i++) {
		printf("%d ", s->elem[i]);
	}
	printf("\n");
}
