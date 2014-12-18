/**
 * @file   cpp_search.cpp
 * @author volovo
 * @date   18.12.2014  
 * @brief  Template search 
 * @detail Sample na genericke vyhledavani v poli libovolnych struktur.
 *         Pouziva template.
 */

#include <iostream>
#include <vector>
#include "tsearch.hpp"

using namespace std;

/**
 * Function main
 * -------------
 * - test 01 - generic search v poli intu
 * - test 02 - generic search v poli stringu
 */
int main(int argc, char **argv) {
	/* test 1 -   */
	cout << " --- TEST 01 --- " << endl;

	vector<int> numbers;
	int p;
	numbers.push_back(78); numbers.push_back(47); numbers.push_back(32); numbers.push_back(40);
	numbers.push_back(7); numbers.push_back(55); numbers.push_back(96); numbers.push_back(13);
	p = tsearch(55, numbers);
	cout << "Position of 55 in numbers is " << p << endl;

 	return 0;
}

