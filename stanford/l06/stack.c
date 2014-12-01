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
 * - test 01 - ineteger stackstack veci
 */
int main(int argc, char *argv[]) {
	/* test 01 - int stack */
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

	/* test 02 - generic stack */

	return 0;
}
