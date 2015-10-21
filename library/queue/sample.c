/**
 * @file sample.c
 * @author volovo
 * @brief priklad s frontou
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "generic_queue.h"

void string_free(void *p) {
	free(*(char **)p);
}

/**
 * Function main
 * -------------
 */
int main(int argc, char *argv[]) {
	/* test 01 - int queue */
	printf("  --- TEST 01 ---\n");
	int ri, i;
	queue qu;
	queue_new(&qu, sizeof(int), NULL);
	for (i = 0; i < 15; i++) {
		queue_push(&qu, &i);
	}
	
	for (i = 0; i < 15; i++) {
		queue_pop(&qu, &ri);
		printf("%d ", ri);
	}
	printf("\n");
	queue_dispose(&qu);

	/* test 03 - generic queue with strings */
	printf("  --- TEST 02 ---\n");
	const char *strs[] = {"aaaaaaa", "bbbbbb", "cc"};
	char * scopy;
	queue_new(&qu, sizeof(char *), string_free);

	for (i = 0; i < 3; i++) {
		scopy = strdup(strs[i]);
		queue_push(&qu,&scopy);
	}

	char *pc;
	for (i = 0; i < 3; i++) {
		queue_pop(&qu, &pc);
		printf("%s ", pc);
		free(pc);
	}
	printf("\n");

	queue_dispose(&qu);

	return 0;
}

