/**
 * Stanford sample
 * 
 * Vaclav Koudelka
 * 13.11.2014
 * Sample na pole, structy, atd.
 */

#include <iostream>
#include <iomanip>

using namespace std;

struct fraction {
	int num;
	int denum;
}

int main(int argc, char **argv) {
	fraction pi;

	pi.num = 22;
	pi.denum = 7;

	cout << "running" << endl;

	return 0;
}

