/* 
 * Stanford sample 
 *
 * Vaclav Koudelka
 * 06.11.2014 
 *  Sample prirazovani hodnot do promennych ruznych typu.
 */

#include <iostream>

using namespace std;

/*
 * This is main function
 */
int main(int argc, char **argv) {
	/* test 1 - 's=c' priradi binarne     */
	{
		char c = 'A';
		short s = c;
		cout << "test 01 ... " << s << endl;
	}
	
	/* test 2 - podobne jako predchozi   */
	{
		short s = 67;
		char c = s;
		cout << "test 02 ... " << c << endl;
	}
	/* test 3 - preteceni pro short      */
	{
		int i = 8388608 + 2097152 + 16384 + 7;             /* 2^23 + 2^21 + 2^14 + 7 */
		short s = i;                                       /* bude oriznuto          */ 
		cout << "test 03 ... " << i << " " << s << endl;
		i = 8388608 + 2097152 + 32768 + 7;                 /* 2^23 + 2^21 + 2^15 + 7 */
		s = i;                                             /* bude oriznuto, ale zmeni se kvuli tomu znamenko */
		cout << "        ... " << i << " " << s << endl;

	}

 	return 0;
}

