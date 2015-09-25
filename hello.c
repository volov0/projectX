/** 
 * @file   hello.c
 * @author Ja Sam
 * @date   07.10.2014 
 * @brief  Nazdar 
 * 
 * Tohle je pokus.
 * See README for more details.
 */

#include <stdio.h>

/**
 * Function main
 * -------------
 */
int main(int argc, char **argv) {
	/**
	 * Initialize.
	 */
	int i, a;
	i = 5;
	a = i++ + i++ + i++;
	printf("Vole a=%d, i=%d\n", a, i);

	i = 5;
	a = ++i + ++i + ++i + ++i;
	printf("Vole a=%d, i=%d\n", a, i);

	/* Return. */
	//return EXIT_SUCCESS;
	return 0;

	/* unreachable */
}

