/**
 * Stanford sample
 * 
 * Vaclav Koudelka
 * 13.11.2014
 * Sample na pole, structy, atd.
 */

#include "../headers/mydefs.h"
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>

#define FRACTION_PRINT(f) f.num << "/" << f.denum

using namespace std;

struct fraction {
	int num;
	int denum;
};

/**
 * Main function
 */
int main(int argc, char **argv) {
	/* test 01 - struct */
	cout << HEADER("TEST 01") << endl;
	struct fraction pi;
	pi.num = 22;
	pi.denum = 7;

	cout << "pi " << FRACTION_PRINT(pi) << endl;
	((fraction *)&(pi.denum))->num = 12;         //to je ale prasarna, menim pi.denum!
	((fraction *)&(pi.denum))->denum = 33;       //jeste hur, prepisuju pamet za pi... buh vi co tam je
	cout << "pi " << FRACTION_PRINT(pi) << endl;

	/* test 02 - pole */
	cout << HEADER("TEST 02") << endl;
    unsigned int p_b[6] = {0xaaaaaaaa, 0xbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff}; // dummy pole, abych videl co je v pameti
	int array[10];              //to, ze tady reknu velikost 10, nema moc smysl... pouze to dokumentuju, v koudu muzu pouzit array[11]
    unsigned int p_a[6] = {0x11111111, 0x2222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666}; // dummy pole, abych videl co je v pameti

	array[0] = 0x9;
	array[5]= 0x55;
	*(array+6) = 0x66;
	array[-18] = 0x200;                   // pretece buhvi kam
	array[12] = 0x100; array[13] = 0x80;  // tohle pretece do pole p_a[0] a p_a[1]
	array[20] = 0x200;                    // tohle pretece do pole p_b[0]

	array[7] = 0x77;                   //nastavim poslednich par bitu
	((short *)array)[15] = 0x7;        //nastavi vice vyznamne bity array[7]

	array[4] = 0x40000;
	((short *)(((char *)(&array[1]))+8))[2] = 0x44;   // vole - prepise bity v array[4];

	cout << "p_b:   " << hex << p_b << " - ";
	for (int i = 0; i < 6; i++)
		cout << hex << p_b[i] << " ";
	cout << endl;

    cout << "array: "<< hex << array << " - ";
	for (int i = 0; i < 10; i++)
		cout << hex << array[i] << " ";
	cout << endl;

	cout << "p_a:   "<< hex << p_a << " - ";
	for (int i = 0; i < 6; i++)
		cout << hex << p_a[i] << " ";
	cout << endl;

	/* test 03 - */
	cout << HEADER("TEST 03") << endl;

	struct students {           
		char *name;        
		char suid[8];
		int  numUnits;
	};

	students pupils[4];                   //tohle bydli v zasobniku (stacku)
	pupils[0].numUnits = 21;
	pupils[2].name = strdup("Pepa");      //strdup - STRing DUPlicate - alokuje misto, kopiruje tam obsah paramteru a vrati adresu
	                                      //  ...Pepa bydli na stacku
	pupils[3].name = pupils[0].suid + 6;  //prasarna
	strcpy(pupils[1].suid,"90210xx");     //strcpy - STRing CoPY - narozdil od strdup NEalokuje pamet
	strcpy(pupils[3].name,"123456");      //ve skutecnosti zapisuje do pupils[0].suid+6 a prepisuje i pupils[0].numUnit a dokonce pupils[1].name

	cout << "pupils[2].name             " << pupils[2].name << endl;     //tady je to jasny, vse je normalni ukazuje na heap
	cout << "pupils[3].name             " << pupils[3].name << endl;     //tohle vyprintuje 123456, interpretuje to adresu, ale
	cout << "pupils[0].numUnits         " << pupils[0].numUnits << endl; //...tady mam ted bordel
	cout << "(char *)&pupils[1].suid[4] " << (char *)&pupils[1].suid[4] << endl; //vyprintuje 0xx

	free(pupils[2].name);      // mel bych uvolnovat naalokovanou pamet 

	
	return 0;
}

