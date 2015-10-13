/**
 * @file   rxml.cpp
 * @author Vaclav Koudelka
 * @brief  XML parser with <thread>
 */

#include <fstream>        
#include "xmlprocessor.h"       


int main(int argc, char **argv) {
	/* read argument */
	if (argc == 1) {
		std::cerr << "You need to specify file." << std::endl;
		return 1;
	}

	/* Inint xml processor */
	XMLProcessor xml_p(argv[1]);

	/* init working threads */
	xml_p.run();

	return 0;
}

