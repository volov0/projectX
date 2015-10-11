/**
 * @file   rxml.cpp
 * @author Vaclav Koudelka
 * @brief  XML parser with <thread>
 */

#include <string>      
#include <iostream>      
#include <fstream>        
#include <thread>             
#include <regex>             
#include "xmlprocessor.h"       


int main(int argc, char **argv) {
	std::ifstream myfile;

	/* read argument */
	/*if (argc == 1) {
		std::cerr << "You need to specify file." << std::endl;
		return 1;
	}*/

	/* Inint xml processor */
	char fn[] = "index.xml";
	//XMLProcessor xml_p(argv[1]);
	XMLProcessor xml_p(fn);

	/* init working threads */
	xml_p.run();

	myfile.close();

	return 0;
}

