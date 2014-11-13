/**
 * Stanford sample
 * 
 * Vaclav Koudelka
 * 13.11.2014
 * Sample na pole, structy, atd.
 */

#include <iostream>
#include <iomanip>

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
	struct fraction pi;

	pi.num = 22;
	pi.denum = 7;

	cout << "pi " << FRACTION_PRINT(pi) << endl;

	((fraction *)&(pi.denum))->num = 12;         //to je ale prasarna, menim pi.denum!
	((fraction *)&(pi.denum))->denum = 33;       //jeste hur, prepisuju pamet za pi... buh vi co tam je
	cout << "pi " << FRACTION_PRINT(pi) << endl;

	return 0;
}

