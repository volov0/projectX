/**
 * @file hack03.c
 * @author volovo
 * @date 21.01.2015
 * @brief Par prasaren.
 * @detail channeling (hahaha) - pouziti veci ze stacku v jine funkci
 *
 * Trochu offtopic poznamka k printf funkci... jeji prototyp vypada takto:
 *   int pritnf(const char *control, ...);
 * Kompilator normalne nekontrlouje jestli to co je misto "..." odpovida control stringu,
 * GCC na to ma ovsem extension.
 * Navratova hodnota printf je pocet %X veci, ktere se podarilo substituovat nebo -1 pri
 * selhani.
 * Kdyz printf() kod dostane kontrolu, tak nevi kolik parametru dohromady je. Pouzije
 * control parametr jako "mapu" a podle toho kolik je tam %X veci, tolik manualne(!)
 * vyzvedne parametru ze stacku 
 */

#include <stdio.h>


void InitArray() {
	int arr[100];
	int i;
	for (i = 0; i < 100; i++) {
		arr[i] = i;      
	}	                 
}

void PrintArray() {
	int arr[100];
	int i;
	for (i = 0; i < 100; i++) {
		printf("%d\n", arr[i]);
	}	                 
}

/**
 * Function main
 * -------------
 */
int main(int argc, char *argv[]) {
	InitArray();
	//printf("Kdyz je tohle odkomentovane tak => Rozmlat to pole co tu je.\n");
	PrintArray();

	return 0;
}
