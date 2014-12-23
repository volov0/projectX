/**
 * @file weird.c
 * @author volovo
 * @date 23.12.2014
 * @brief Sample na linkovani - hack.
 * @detail
 * Ukazka divneho volani standartni funkce, ktere ovsem funguje.
 * 
 */

/* Podotykam, ze zde umyslne chybi #include <string.h>... jinak by to neproslo. */
#include <stdio.h>

int strlen(char *s, int l);    // hahaha - vlastni (spatna) prototyp, ale to nevadi

/**
 * Function main
 * -------------
 * -
 */
int main(int argc, char *argv[]) {
	int n = 65;
	/* Nasledujici volani se provede, kompilace hodi warning,
	 * Linker najde standartni funkci strlen, ktera bere jen
	 * jeden parametr, takze ten druhy bude ignorovat (ze stacku)
	 * ho proste nebere. */
	int len = strlen((char *)&n, n);
	printf("length = %d\n", len);
	return 0;
}
