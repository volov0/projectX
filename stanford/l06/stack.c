/**
 * @file stack.c
 * @author volovo
 * @date 1.12.2014
 * @brief stack implementace
 */

#include <stdio.h>
#include "int_stack.h"
#include "generic_stack.h"

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
	stack_new(&st, sizeof(int));
	for (i = 0; i < 15; i++) {
		stack_push(&st, &i);
	}
	
	for (i = 0; i < 15; i++) {
		pi = stack_pop(&st);
		printf("%d ", *pi);
	}
	stack_dispose(&st);

	/* test 02 - generic stack with ints */



	return 0;
}
