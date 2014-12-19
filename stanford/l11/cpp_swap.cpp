/**
 * @file cpp_swap.cpp
 * @author volovo
 * @date 19.12.2014
 * @brief jednoduchy swap, cil je ukazat rozdil mezi pointerem
 *    a c++ referenci ve strojovem kodu
 * @detail poznamka k referencim:
 *   int &z = x;   // reference
 *   int *z = &x;  // pointer
 *   - z hlediska assembly kodu predchozi dve veci udelaji totez
 *   Rozdil mezi referenci a pointerem je ten, ze reference je 
 *   akorat jeni pojmenovani pro promennou, ktera se k ni vaze.
 *   Referenci nelze menit, vzdy ukazuje na to, co se k ni prvne
 *   priradilo.
 *   Vyhoda reference je ta, ze se jednou definuje a pak uz se 
 *   vsude nemusi pouzivat *, kompilator tam adresy prelozi sam.
 *   Kdyz funkce(metoda) vraci referenci, program se chova uplne 
 *   jako by funkce vracela hodnotu, ale kompilator to ve skutecnosti
 *   prelozi tak, ze funkce vraci pointer.
 */

#include <iostream>
using namespace std;

/* Assebler kod pro tuhle funkci je uplne stejny jako pro c funkci
 * s pointerama - kompilator to tak prechrousta. */
void swap(int &a, int &b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int main(int argc, char *argv[]) {
	int x, y;
	x = 10;
	y = 20;
	cout << "x = " << x << ", y = " << y << endl << "swap" << endl;
	/* Nasledujici volani nepredava parametry hodnotou ale referenci
	 * kompilator totiz, vi ze protopty swap ma c++ reference. Tak 
	 * tam automaticky soupne reference. - viz assemler kod */
	swap(x, y);
	cout << "x = " << x << ", y = " << y << endl;
	return 0;
}
