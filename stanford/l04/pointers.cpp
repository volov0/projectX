/**
 * @file   pointers.cpp
 * @author Vaclav Koudelka
 * @date   20.11.2014
 * @brief  Stanford sample 
 *
 * Sample na pole, funkce...
 */

#include "../headers/mydefs.hpp"
#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

void swap_int(int *ap, int *bp);
void swap(void *vp1, void *vp2, int size);
void swap_my(void *vp1, void *vp2, int size);
int  lsearch_int(int key, int array[], int size);
void *lsearch_mem(void *key, void *base, int n, int elem_size);

/**
 * Function main
 * -------------
 * - test 01 - simple int swap 
 * - test 02 - !!!!Pozor tohle je dulezite!!!!
 *   - Kdyz swapuju inty, swap predam jako parametry adresy intu - int *
 *   - Kdyz swapuju stringy (char *), musim swapu predat adresu, kde je adresa stringu
 *     swap vubec nevi o tom, ze tam jsou nejake stringy prehodi pouze obsah adres na stacku,
 *     ktere ukazuji nekam na heap.
 *   - Takze swap dostane adresu adresy - char **
 * - test 03 - simple int search
 * - test 04 - 
 */
int main(int argc, char **argv) {

	cout << "sizeof char *:" << sizeof(char *) << endl;
	/* test 01 */
	cout << HEADER("TEST 01") <<endl;
	int x = 20; 
	int y = 50;
	cout << "x = " << x << ", y = " << y << endl;
	swap_int(&x,&y);
	cout << "x = " << x << ", y = " << y << endl;
	swap(&x,&y, sizeof(int));
	cout << "x = " << x << ", y = " << y << endl;
	swap_my(&x,&y, sizeof(int));
	cout << "x = " << x << ", y = " << y << endl;

	short s = 4;
	swap(&x,&s, sizeof(int));   
	cout << "x = " << x << ", s = " << s << endl;

	/* test 02 */ 
	cout << HEADER("TEST 02") << endl;
	char *husband = strdup("Pepa Zdepa");
	char *wife    = strdup("Brunhilda von Bahnhof");
	cout << setw(25) << left << "&husband: " << &husband << endl;
	cout << setw(25) << left << "husband:  " << husband << endl;
	cout << setw(25) << left << "*husband: " << *husband << endl;
	cout << setw(25) << left << "&wife:    " << &wife << endl;
	cout << setw(25) << left << "wife:     " << wife << endl;
	cout << setw(25) << left << "*wife:    " << *wife << endl;
	cout << setw(25) << left << "(int *)husband:" << (int *)husband << endl;                    //zobrazi adresu na heapu kde je "Pepa"
	cout << setw(25) << left << "<static_cast>husband:" << static_cast<void*>(husband) << endl; //totez jako predchozi
	cout << setw(25) << left << "(int *)wife: " << (int *)wife << endl;                         //zobrazi adresu na heapu kde je "Brunhilda"
	cout << setw(25) << left << "<static_cast>wife:" << static_cast<void*>(wife) << endl;       //totez jako predchozi
	/* udelam swap */
	cout << "-- swap(&husband,&wife,sizeof(char *))" << endl;
	swap(&husband, &wife, sizeof(char *));
	cout << setw(25) << left << "&husband: " << &husband << endl;
	cout << setw(25) << left << "husband   " << husband << endl;
	cout << setw(25) << left << "*husband  " << *husband << endl;
	cout << setw(25) << left << "&wife:    " << &wife << endl;
	cout << setw(25) << left << "*wife:    " << *wife << endl;
	cout << setw(25) << left << "*wife:    " << *wife << endl;
	cout << setw(25) << left << "(int *)husband:" << (int *)husband << endl;                    //zobrazi adresu na heapu kde je "Pepa"
	cout << setw(25) << left << "<static_cast>husband:" << static_cast<void*>(husband) << endl; //totez jako predchozi
	cout << setw(25) << left << "(int *)wife: " << (int *)wife << endl;                         //zobrazi adresu na heapu kde je "Brunhilda"
	cout << setw(25) << left << "<static_cast>wife:" << static_cast<void*>(wife) << endl;       //totez jako predchozi
	/* problem C a takovych veci, je to, ze jde snadno udelat chyba kvuli 
	 * generickym void pointerum.
	 * Nasledujici swap lze zkompilovat... prekladac nepozna, ze to je blbe,
	 * ale blbe to je... */
	cout << "-- swap(husband,wife,sizeof(char *)) ... chybne zadane parametry" << endl;
	swap(husband, wife, sizeof(char *));
	cout << "-- husband: " << husband << ", wife: "<< wife << endl;

	/* test 03 */
	cout << HEADER("TEST 03") << endl;
	int arr[10] = {15, 30, 48, 78, 46, 7, 13, 47, 69, 11};
	int kk;
	kk = lsearch_int(13, arr, 10);
	cout << "position of 13 in array is " << kk << endl;
	
	int *pk;
	int key = 47;   // musim vytvorit promennou, protoze budu predavat jako &key
	pk = (int *)lsearch_mem(&key, arr, 10, sizeof(int));
	cout << "position of 47 in array is " << pk - arr << endl;
	cout << "arr: " << arr << endl;
	cout << "pk:  " << pk  << endl;

	return 0;
}

/**
 * Function: swap_int
 * ------------------
 * Jednoduchy swap... prehodi pouze integery
 * @param ap pointer na prvni int
 * @param bp pointer na druhy int
 */
void swap_int(int *ap, int *bp) {
	int temp = *ap;
	*ap = *bp;
	*bp = temp;
}

/**
 * Function: swap
 * -----------------
 * Genericky swap... prehodi dve jakekoliv vecipo bitech
 *                   navic tam vyprintuju parametry
 * @param vp1 pointer na prvni vec
 * @param vp2 pointer na druhou vec
 * @param size velikost dat k prehozeni
 *             muze se dat const, ale const se obecne pouziva
 *             pri sdileni dat 
 */
void swap(void *vp1, void *vp2, int size) {
	char buffer[size];   // je mozne urcit velikost pole z parametru funkce v g++
	                     // ANSI C to ale zakazuje... smi tam byt jen konstanta
						 // musi se vypnout warningy kompilatoru
	#if DEBUG
		cout << "## in swap ## vp1: " << hex << vp1 << ", vp2: " << hex << vp2 << endl;
		cout << "## in swap ## *(int *)vp1: " << hex << *(int *)vp1 << ", *(int *)vp2: " << hex << *(int *)vp2 << endl;
	#endif
	memcpy(buffer, vp1, size);
	memcpy(vp1, vp2, size);
	memcpy(vp2, buffer, size);
}

/**
 * Function: swap_my
 * -----------------
 * Genericky swap... prehodi dve jakekoliv veci po bitech, moje verze
 *                   je tu problem, ze kopiruje od konce...
 * @param vp1 pointer na prvni vec
 * @param vp2 pointer na druhou vec
 * @param size velikost dat k prehozeni
 *             muze se dat const, ale const se obecne pouziva
 *             pri sdileni dat 
 */
void swap_my(void *vp1, void *vp2, int size) {
	char buffer;     
	while (size--) {
		buffer = ((char *)vp1)[size];
		((char *)vp1)[size] = ((char *)vp2)[size];
		((char *)vp2)[size] = buffer;
	}
}

/**
 * Function lsearch_int
 * --------------------
 * Jednoduche prohledavani pole, zvladne pouze pole integeru.
 * @return cislo pozice klice v poli
 * @param1 key klic toho co se hleda v poli
 * @param2 array pole ve kterem se hleda
 * @param3 size velikost pole
 */
int lsearch_int(int key, int array[], int size) {
	for (int i = 0; i < size; i++) {
		if (key == array[i]) {
			return i;
		}
	}
	return -1;
}

/**
 * Function lsearch_mem
 * --------------------
 * Castecne genericka funkce pro prohledavani pole, ktere obsahuje jakekoliv veci.
 * @return adresa na prvek v poli, ktery odpovida klici
 * @param1 key klic toho, co se hleda v poli
 * @param2 base adresa zacatku pole
 * @param3 n pocet prvku v poli
 * @param4 elem_size velikost jednoho prvku
 * 
 * Pro porovnani pouziva memcmp, takze neni vhodna pro struktury s pointrama
 * nebo stringy.
 */
void * lsearch_mem(void *key, void *base, int n, int elem_size) { 
	for (int i = 0; i < n; i++) {
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
		if (memcmp(key,element_addr,elem_size) == 0) {
			return element_addr;
		}
	}
	return NULL;
}

