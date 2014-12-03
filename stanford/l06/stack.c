/**
 * @file stack.c
 * @author volovo
 * @date 1.12.2014
 * @brief stack implementace
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "int_stack.h"
#include "generic_stack.h"

void intcpy(void *dest, void *src);
void stringcpy(void *dest, void *src);
/**
 * Function main
 * -------------
 * - test 01 - ineteger stack 
 * - test 02 - genericky stack
 */
int main(int argc, char *argv[]) {
	/* test 01 - int stack */
	printf("  --- TEST 01 ---\n");
	int_stack is;
	int_stack_new(&is);
	int i;
	 
	for (i = 0; i < 15; i++) {
		int_stack_push(&is, i);
	}
	int_stack_print(&is);
	i = int_stack_pop(&is);
	i = int_stack_pop(&is);
	int_stack_print(&is);
	int_stack_dispose(&is);

	/* test 02 - generic stack with ints */
	printf("  --- TEST 02 ---\n");
	int *pi;
	stack st;
	stack_new(&st, sizeof(int), intcpy);
	for (i = 0; i < 15; i++) {
		stack_push(&st, &i);
	}
	
	for (i = 0; i < 15; i++) {
		pi = stack_pop(&st);
		printf("%d ", *pi);
	}
	printf("\n");
	stack_dispose(&st);

	/* test 03 - generic stack with strings */
	printf("  --- TEST 03 ---\n");
	stack_new(&st, sizeof(char *), stringcpy);

	stack_push(&st, "aaaa");
	stack_push(&st, "bbbb");
	stack_push(&st, "aAcc");
	stack_push(&st, "ddaa");
	stack_push(&st, "aaee");
	stack_push(&st, "ffaa");
	stack_push(&st, "aagg");
	stack_push(&st, "hhaa");
	stack_push(&st, "aaii");
	stack_push(&st, "ajja");
	
	char *pc;
	for (i = 0; i < 10; i++) {
		pc = stack_pop(&st);
		printf("%s ", pc);
	}
	printf("\n");



	return 0;
}

/**
 * Function intcpy
 * ---------------
 * @dest destination
 * @src source
 * @brief copy  integers
 */
void intcpy(void *dest, void *src) {
	int *d = dest;
	int *s = src;
	*d = *s;
}

/**
 * Function stringcpy
 * ------------------
 * @dest destination
 * @src source
 * @brief copy strings
 */
void stringcpy(void *dest, void *src) {
	char *d;
	char *s = src;
	d = strdup(s);
	assert(dest != NULL);
	memcpy(dest, d, sizeof(char *));
}
