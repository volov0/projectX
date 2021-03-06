/**
 * @file stack.c
 * @author volovo
 * @date 1.12.2014
 * @brief stack implementace
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "int_stack.h"
#include "../../library/stack/generic_stack.h"

void string_free(void *p) {
	free(*(char **)p);
}

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
	int ri;
	stack st;
	stack_new(&st, sizeof(int), NULL);
	for (i = 0; i < 15; i++) {
		stack_push(&st, &i);
	}
	
	for (i = 0; i < 15; i++) {
		stack_pop(&st, &ri);
		printf("%d ", ri);
	}
	printf("\n");
	stack_dispose(&st);

	/* test 03 - generic stack with strings */
	printf("  --- TEST 03 ---\n");
	const char *strs[] = {"aaaaaaa", "bbbbbb", "cc"};
	char * scopy;
	stack_new(&st, sizeof(char *), string_free);

	for (i = 0; i < 3; i++) {
		scopy = strdup(strs[i]);
		stack_push(&st,&scopy);
	}

	char *pc;
	for (i = 0; i < 3; i++) {
		stack_pop(&st, &pc);
		printf("%s ", pc);
		free(pc);
	}
	printf("\n");

	stack_dispose(&st);

	return 0;
}

