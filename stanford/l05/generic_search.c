/**
 * @file   generic_search.c 
 * @author Vaclav Koudelka
 * @date   24.11.2014
 * @brief  Sample an funkce a pointery
 *
 * Genericky search prohledava pole libovolnych struktur.
 * Jako parametr zere pointer na porovnavaci funkci.
 * Zde pracuju s intem, ale lze zmenit na cokoliv jineho.
 * Nasledujici kod nelze zkompilovat s g++, neni to totiz c++.
 * Funkci compare_int nelze v c++ protlacit do lsearch...
 */

#include <stdio.h>

int  compare_int(void *a, void *b);
void *lsearch(void *key, void *base, int n, int elem_size, int (*cmpfn)(void *, void *));

/**
 * Function main
 * -------------
 * - test 01 - generic vyhledavani v poli
 *     - pole muze obsahovat libovolne struktury 
 *     - je potreba dodat porovnavaci funkci
 */
int main(int argc, char **argv) {
	printf("  --- TEST 01 ---\n");

	int arr[10] = {78, 47, 32, 40, 7, 55, 96, 1, 72, 20 };
	int *pk;
	int key = 96;
	pk = lsearch(&key, arr, 10, sizeof(int), compare_int);
	printf("position of %d in array id %lu \n", key, pk - arr);
	printf("arr:  %lx\n", (long)arr); 
	printf("pk:   %lx\n", (long)pk);

	return 0;
}

/**
 * Function lsearch
 * --------------------
 * Genericka funkce pro prohledavani pole, ktere obsahuje jakekoliv veci.
 * @return adresa na prvek v poli, ktery odpovida klici
 * @param1 key klic toho, co se hleda v poli
 * @param2 base adresa zacatku pole
 * @param3 n pocet prvku v poli
 * @param4 elem_size velikost jednoho prvku
 * @param5 cmpfn funkce pro porovnani dvou prvku
 */
void *lsearch(void *key, void *base, int n, int elem_size, int (*cmpfn)(void *, void *)) {
	int i;
	for (i = 0; i < n; i++) {
		/* poznamka k nasledujicimu prirazeni:
		 *  - i*elem_size je offset od zacatku pole
		 *  - (char *)base - tady musi byt pretypovani na (char *) protoze,
		 *    ANSI C nedovluje aritmetiku s typem (void*), takze pretypovani
		 *    na (char *) nic nezmeni jen kompilator nebude hazet warningy
		 *    je to hack, ale bezne se pouziva
		 *  - v podstate delam pointerovou aritmetiku brutalni silou na misto
		 *    kompilatoru... ten totiz nemuze vedet jak... opet je to problem C
		 */
		void *element_addr = (char *)base + i*elem_size;
		if (cmpfn(key,element_addr) != 0) {
			return element_addr;
		}
	}
	return NULL;
}

/**
 * Function compare_int
 * --------------------
 * @return true if int parameters are equal otherwise false
 * @param1 number 1
 * @param2 number 2
 */
int compare_int(void *a, void *b) {
	int *p1 = a;
	int *p2 = b;

	return *p1 == *p2;
}
