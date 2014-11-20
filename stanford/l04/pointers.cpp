/**
 * Stanford sample 
 *
 * Vaclav Koudelka
 * 20.11.2014
 * Sample na pole, funkce...
 */

#include "../headers/mydefs.h"
#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

void swap_int(int *ap, int *bp);
void swap(void *vp1, void *vp2, int size);
void swap_my(void *vp1, void *vp2, int size);

int main(int argc, char **argv) {

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
	swap(&x,&s, sizeof(int));   // noahodou funguje
	cout << "x = " << x << ", s = " << s << endl;

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
 * @param vp1 pointer na prvni vec
 * @param vp2 pointer na druhou vec
 * @param size velikost dat k prehozeni
 */
void swap(void *vp1, void *vp2, int size) {
	char buffer[size];   // je mozne urcit velikost pole z parametru funkce v g++
	                     // ANSI C to ale zakazuje... smi tam byt jen konstanta
						 // musi se vypnout warningy kompilatoru 
	memcpy(buffer, vp1, size);
	memcpy(vp1, vp2, size);
	memcpy(vp2, buffer, size);
}

/**
 * Function: swap_my
 * -----------------
 * Genericky swap... prehodi dve jakekoliv veci po bitech, moje verze
 * @param vp1 pointer na prvni vec
 * @param vp2 pointer na druhou vec
 * @param size velikost dat k prehozeni
 */
void swap_my(void *vp1, void *vp2, int size) {
	char buffer;     
	while (size--) {
		buffer = ((char *)vp1)[size];
		((char *)vp1)[size] = ((char *)vp2)[size];
		((char *)vp2)[size] = buffer;
	}
}

