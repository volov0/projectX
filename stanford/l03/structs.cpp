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

	/* test 01 - struct */
	cout << "pi " << FRACTION_PRINT(pi) << endl;

	((fraction *)&(pi.denum))->num = 12;         //to je ale prasarna, menim pi.denum!
	((fraction *)&(pi.denum))->denum = 33;       //jeste hur, prepisuju pamet za pi... buh vi co tam je
	cout << "pi " << FRACTION_PRINT(pi) << endl;

	/* test 02 - pole */
    unsigned int p_b[6] = {0xaaaaaaaa, 0xbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff}; // dummy pole, abych videl co je v pameti
	int array[10];              //to, ze tady reknu velikost 10, nema moc smysl... pouze to dokumentuju, v koudu muzu pouzit array[11]
    unsigned int p_a[6] = {0x11111111, 0x2222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666}; // dummy pole, abych videl co je v pameti

	array[5]= 44;
	array[-18] = 512;                  // pretece buhvi kam
	array[12] = 256; array[13] = 128;  // tohle pretece do pole p_a[0] a p_a[1]
	array[20] = 512;                   // tohle pretece do pole p_b[0]

	cout << "test 02" << endl << "        p_b:   " << hex << p_b << " - ";
	for (int i = 0; i < 6; i++)
		cout << hex << p_b[i] << " ";
	cout << endl;

   cout << "        array: "<< hex << array << " - ";
	for (int i = 0; i < 10; i++)
		cout << dec << array[i] << " ";
	cout << endl;

	cout << "        p_a:   "<< hex << p_a << " - ";
	for (int i = 0; i < 6; i++)
		cout << hex << p_a[i] << " ";
	cout << endl;
	
	return 0;
}

