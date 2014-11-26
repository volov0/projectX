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
 *
 * Nove programovaci jazyky pouzivaji jine zpusoby pro genericky 
 * kod (napr. C++ ma templaty). Da se rict, ze nove jazyky se 
 * poucily z chyb C. Nevyhoda C je, ze kompilator nema sanci nic 
 * kontrolovat (nevi jake typy tam maji byt misto void*). Vyhoda
 * je, ze je to rychle. V pameti je vzdy pouze jedna instance
 * lsearch funkce na vyhledavani v jakychkoliv polich jakychkoliv 
 * typu. C++ templaty maji pro kazdy typ vlastni instanci lsearch
 * kodu.
 */

#include <stdio.h>
#include <string.h>

int  compare_int(void *e1, void *e2);
int  compare_string(void *e1, void *e2);
void *lsearch(void *key, void *base, int n, int elem_size, int (*cmpfn)(void *, void *));

/**
 * Function main
 * -------------
 * - test 01 - genericke vyhledavani v poli
 *     - pole muze obsahovat libovolne struktury 
 *     - je potreba dodat porovnavaci funkci
 * - test 02 - misto intu vyhledavam ve string poli
 */
int main(int argc, char **argv) {
	/* test 01 */
	{
		printf("  --- TEST 01 ---\n");

		int arr[10] = {78, 47, 32, 40, 7, 55, 96, 1, 72, 20 };
		int *pk;
		int key = 96;
		pk = lsearch(&key, arr, 10, sizeof(int), compare_int);
		printf("position of %d in array id %lu \n", key, pk - arr);
		printf("arr:  %lx\n", (long)arr); 
		printf("pk:   %lx\n", (long)pk);
	}

	/* test 02 */
	{
		printf("  --- TEST 02 ---\n");

		/* pokud definuju pole stringu takto, potom jednotlive 
		 * stringy jsou globalni promenne (ktere jsou konstanty) -
		 *  - jsou jako normalni globalni promenne az na to, ze to
		 *    jsou "char" pole a pri loadovani programu jsou nahrazenne
		 *    hodnotami (hole, empty, ...) 
		 */
		char *arr[7] = {"hole", "empty", "void", "naught", "dummy", "kennel", "0o0o0o0o" };
		char **pk;    /*  */
		char *key = "void";
		pk = lsearch(&key, arr, 7, sizeof(char *), compare_string);
		printf("position of %s in array id %lu \n", key, pk - arr);
		printf("arr:  %lx\n", (long)arr); 
		printf("pk:   %lx\n", (long)pk);
	}

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
 *         * pred cmpfn byla pred casem vyzadovana a ted uz neni, asi
 *         je lepsi ji tam davat (z historickych duvodu), * rika, ze cmpfn
 *         je pointer na funkci, dnes uz to komiplatory poznaji i bez *
 *         zavorky jsou z duvodu lepsi citelnosti  
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
		if (cmpfn(key,element_addr) == 0) {
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
int compare_int(void *e1, void *e2) {
	int *p1 = e1;
	int *p2 = e2;

	return *p1 - *p2;
}

/**
 * Function compare_string
 * -----------------------
 * @return true if int parameters are equal otherwise false
 * @param1 ve skutecnosti dostane typ char **, coz je pointer na string,
 *         coz je adresa ukazujici na adresu, ktera ukazuje na adresu 
 *         prvniho znaku stringu
 * @param2 ve skutecnosti dostane typ char **, stejne jako @param1     
 */
int compare_string(void *e1, void *e2) {
	/* nasledujici kod:
	 * potrebuju pretypovat na char** protoze nelze dereferencovat void* 
	 * (= nemuzu delat *e1 na void*)
	 * pokud by platilo void **e1, pak lze delat jednu dereferenci, e1 by 
	 * totiz ukazovalo na void*
	 */
	char *p1 = *(char **)e1; 
	char *p2 = *(char **)e2;

	return strcmp(p1, p2);
}
