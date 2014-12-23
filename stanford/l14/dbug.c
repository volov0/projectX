/**
 * @file dbug.c
 * @author volovo
 * @date 23.12.2014
 * @brief Bezne C chyby.
 */

#include <string.h>
#include <stdio.h>



/**
 * Function main
 * -------------
 * - segmentation fault
 * - bus error
 */
int main(int argc, char *argv[]) {
	int *pi = NULL;
	
	if (argc < 2) {
		printf("Specify -s -b or something to get error.\n");
		return 0;
	}
	/* seg fault - dereferencuju neco co nejde */
	if (strcmp(argv[1],"-s") == 0) {
		*pi = 5;
	}

	/* bus error - vsechny inty bydli na adrese delitelne 4 - 
	 * - ovsem x86 procesor na to sere a vse zvlada a bus error
	 * nehaze... musi se nastavit alignment checking.  */
	if (strcmp(argv[1],"-b") == 0) {
		#if defined(__GNUC__)
			#if defined(__i386__)
			/* Enable Alignment Checking on x86 */
				__asm__("pushf\norl $0x40000,(%esp)\npopf");
			#elif defined(__x86_64__) 
			/* Enable Alignment Checking on x86_64 */
				__asm__("pushf\norl $0x40000,(%rsp)\npopf");
			#endif
		#endif

		char s[10] = "abcdefgh";
		pi = (int *)s;
		*pi = 0x70707070;
		printf("%lx %lx \n", (unsigned long)s, (unsigned long)pi);
		printf("First assignment ... ok %s \n", s);
		pi = (int *)(s + 1);
		printf("%lx %lx \n", (unsigned long)s, (unsigned long)pi);
		*pi = 0x66666666;
		printf("Second assignment ... ok %s \n", s);
	}


	return 0;
}
