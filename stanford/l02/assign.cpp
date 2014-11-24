/**
 * @file   assign.cpp
 * @author Vaclav Koudelka
 * @date   06.11.2014  
 * @brief  Stanford sample 
 * 
 *  Sample prirazovani hodnot do promennych ruznych typu.
 */


#include "../headers/mydefs.hpp"
#include <iostream>
#include <iomanip>



using namespace std;

/**
 * Function main
 * -------------
 * - test 01 - 's=c' priradi binarne... implicitni konverze char->short
 * - test 02 - test 01, ale konverze naopak
 * - test 03 - implicitni konverze int->short, dojde k orezavani bytu a zmene znaminka
 * - test 04 - konverze short->int
 * - test 05 - hexadecimalni vypis float
 * - test 06 - prekopirovani bitu int(i=37) do float cisla + hexadecimalni vypis
 * - test 07 - prekopirovani bitu float(f=517) do short cisla + hexadecomalni vypis obou
 */
int main(int argc, char **argv) {
	cout << "size of int:   " << sizeof(int) << endl << "size of short: " << sizeof(short) <<endl;
	cout << "size of float: " << sizeof(float) << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	/* test 1 - 's=c' priradi binarne     */
	{
		char  c = 'A';
		short s = c;

		cout << HEADER("TEST 01") << endl;
		cout << s << " s=c ... char to short conversion, nothing is lost." << endl;
	}
	
	/* test 2 - podobne jako predchozi   */
	{
		short s = 67;
		char  c = s;

		cout << HEADER("TEST 02") << endl;
		cout << c << " c=s ... short to char conversion, something can be lost, but not his time." << endl;
	}
	/* test 3 - preteceni pro short      */
	{
		int   i = 8388608 + 2097152 + 16384 + 7;           // 2^23 + 2^21 + 2^14 + 7   
		short s = i;                                       // bude oriznuto             

		cout << HEADER("TEST 03") << endl;
		cout << i << " " << s << "  s=i int to short conversion, two upper bytes are lost (i=2^23+2^21+2^14+7)." << endl;
		i = 8388608 + 2097152 + 32768 + 7;                 // 2^23 + 2^21 + 2^15 + 7   
		s = i;                                             // bude oriznuto, ale zmeni se kvuli tomu znamenko   
		cout << i << " " << s << " s=i int to short conversion, two upper bytes lost, ";
		cout << "value misinterpreted as negative (i=2^23+2^21+2^15+7)." << endl;
    }
	{
		short s = -1;       // binarne vypada s tak, ze vsechny bity jsou 1   
		int   i = s;        // byty ktere ma int navic oproti short se doplni jednickama
		                    // aby nedoslo k destrukci cisla, takze i jsou ted taky same bitove jednicky    
		cout << HEADER("TEST 04") << endl;
		cout << i << " i=s short to int conversion, i=-1 - two bytes which are added are populated with binary 1";
		cout << " - two's complement." << endl;					   
	}
	/**
	 * test 5 reprezentace float:
	 * ==============================================================================
	 * ||+/-| <------ 8b ------> | <-------------------- 23b --------------------> ||  
	 * ==============================================================================
	 *               exp                              xxxxxxxx
	 *  s ... +- znamenko je 1 bit
	 *
	 *  (-1)^s * 1.xxxxxx*2^(exp-127)  je reprezentace cisla
	 *     xxxxxx = b1*2^(-1) + b2*2^(-2) + ... + b23*2^(-23)
	 *
	 *  napr. 7 = 1.75*2^(2) = 1.75*4 = 7  
	 */
	 {
		 float f = 7;
		 char *c = (char *)&f;
		 
		 cout << HEADER("TEST 05") << endl;
		 cout << "0x";
		 for (int i = sizeof(float) - 1; i >= 0; i--)
			cout << setw(2) << setfill('0') << hex << ((short)c[i] & 0xff);
		 cout << "   float f = 7 - hex content of memory." << endl;

	 }
	 /* test 6  */ 
	 {
		 int   i = 37;
		 float f = *(float *)&i;    // prekopiruje bity nikoliv hodnotu   
		 char *c = (char *)&f;

		 cout << HEADER("TEST 06") << endl;
		 cout << dec << i << " " << f << "   copying bits from int i=37 to float" << endl;
		 cout << "0x";
		 for (int i = sizeof(float) - 1; i >= 0; i--)
			cout << setw(2) << setfill('0') << hex << ((short)c[i] & 0xff);
		 cout << "      resulting float is dumped." << endl;
	 }
	 /*  test 7  */
	 {
		 float f = 517.0;
		 short s = *(short *)&f;   // prekopiruje pouze bity z prvnich 2 bytu !    
		 char *c = (char *)&f;

		 cout << HEADER("TEST 07") << endl;
		 cout << dec << f << " " << s << "       copying bits from float f=517 to short => two bytes are discarded." << endl;     
		 cout << "0x";
		 for (int i = sizeof(float) - 1; i >= 0; i--)
			cout << setw(2) << setfill('0') << hex << ((short)c[i] & 0xff);
		 cout << "      float f=517 dump." << endl;

		 cout << "0x";
		 for (int i = sizeof(short) - 1; i >= 0; i--)
			cout << setw(2) << setfill('0') << hex << ((short)c[i] & 0xff);
		 cout << "          short s containing two lower bits from float f=517." << endl;
	 }
    

 	return 0;
}

