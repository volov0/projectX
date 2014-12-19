/**
 * @file cpp_swap.cpp
 * @author volovo
 * @date 19.12.2014
 * @brief jednoduchy swap, cil je ukazat rozdil mezi pointerem
 *    a c++ referenci ve strojovem kodu
 */

#include <iostream>
using namespace std;

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
	swap(x, y);
	cout << "x = " << x << ", y = " << y << endl;
	return 0;
}
