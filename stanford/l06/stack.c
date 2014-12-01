/**
 * @file stack.c
 * @author Vaclav Koudelka
 * @date 1.12.2014
 * @brief stack implementace
 */

#include <stdio.h>
#include "int_stack.h"

/**
 * Function main
 * -------------
 * - test 01 - ineteger stackstack veci
 */
int main(int argc, char *argv[]) {
	/* test 01 - int stack */
	int_stack is;
	int_stack_new(&s);
	for (int i = 0; i < 5; i++) {
		int_stack_push(&is, i);
	}
	int_stack_print(&s);
	int_stack_dispose(&s);

	/* test 02 - generic stack */

	return 0;
}
