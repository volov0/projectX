/**
 * @file hack02.c
 * @author volovo
 * @date 23.12.2014
 * @brief Par prasaren.
 * @detail prepisuju si navratovou adresu ve funkci
 */

#include <string.h>
#include <stdio.h>


void foo() {
	int arr[4];
	int i;
	// dump
	for (i = 0; i <= 7; i++) {
		arr[i] -= 4;          // postupem casu prepise navratovou adresu 
	}	                      // do main -> tam se dela znpova CALL foo
}

/**
 * Function main
 * -------------
 */
int main(int argc, char *argv[]) {
	foo();

	return 0;
}
