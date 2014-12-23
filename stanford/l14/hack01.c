/**
 * @file hack01.c
 * @author volovo
 * @date 23.12.2014
 * @brief Par prasaren.
 * @detail buffer overflow with loop 
 */

#include <string.h>
#include <stdio.h>



/**
 * Function main
 * -------------
 */
int main(int argc, char *argv[]) {
	int i;
	int arr[4];
	// todo: dump memory
	for (i = 0; i <= 7; i++) {   
		arr[i] = 0;            // postupem casu to vzdy prepisu i na 0
		printf("%d %d -- ", arr[i], i);
	}

	return 0;
}
