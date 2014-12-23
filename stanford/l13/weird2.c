/**
 * @file weird2.c
 * @author volovo
 * @date 23.12.2014
 * @brief Sample na linkovanik.
 * @detail
 * Ukazka dalsiho divneho volani standartni funkce.
 * C C++ neco takoveho nelze, kompilator nebo linker by vyhodil chybu.
 * V C++ lze delat pretezovani funkci - Ruzne definice funkce stejneho jmena
 * pro ruzne typy prametru... Coz znamena, ze C++ kompilator, vygeneruje volani
 * C++ funkce nejak takhle: "CALL memcmp_void_p" a linker potom bude hledat 
 * funkci memcmp, ktera bere void* jako parametr a tu nenajde...
 */

/* Podotykam, ze zde umyslne chybi #include <string.h>... jinak by to neproslo. */
#include <stdio.h>

int memcmp(void *m);    // vlastni prototyp, memcmp normalne bere 3 argumenty
                        // int memcpm(void *v1, void *v2, int len)

/**
 * Function main
 * -------------
 * -
 */
int main(int argc, char *argv[]) {
	int n = 17;
	/* Nasledujici volani se provede, kompilace hodi warning,
	 * Linker najde standartni funkci memcmp, ktera bere tri
	 * parametry. Opravdu si je ze stacku vezme a je otazka 
	 * co se stane potom. Pravdepodobne to spadne... */
	int m = memcmp(&n);
	printf("m = %d\n", m);
	return 0;
}
