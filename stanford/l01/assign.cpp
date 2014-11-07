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
	cout << "size of int:   " << sizeof(int) << endl << "size of short: " << sizeof(short) <<endl;
	cout << "size of float: " << sizeof(float) << endl;
	cout << "--------------------------------" << endl;
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
	{
		short s = -1;       /* binarne vypada s tak, ze vsechny bity jsou 1 */
		int i = s;          /* byty ktere ma int navic oproti short se doplni jednickama
		                       aby nedoslo k destrukci cisla, takze i jsou ted taky same bitove jednicky  */
		cout << "test 04 ... " << s << " " << i << endl;					   
	}
	/*
	 * test 4 reprezentace float:
	 * ==============================================================================
	 * ||+/-| <------ 8b ------> | <-------------------- 23b --------------------> ||  
	 * ==============================================================================
	 *               exp                              xxxxxxxx
	 *  s ... +- znamenko je 1 bit
	 *
	 *  (-1)^s * 1.xxxxxx*2^(exp-127)  je reprezentace cisla
	 *
	 *  napr. 7 = 1.75*2^(2) = 1.75*4 = 7 
	 */
	 {
		 float f = 7;
		 /* todo vyprintovat hexdec a binarne */
	 }
	 /* test 5  */
	 {
		 int i = 37;
		 float f = *(float *)&i;    /* prekopiruje bity nikoliv hodnotu */
		 cout << "test 05 ... " << i << " " << f << endl;
	 }
	 /*  test 666666  */
	 {
		 float f = 517.0;
		 short s = *(short *)&f;   /* prekopiruje pouze bity z prvnich 2 bytu !  */
		 cout << "test 06 ... " << f << " " << s << endl;  /* todo: proc je tam 0? */
	 }
    

 	return 0;
}

