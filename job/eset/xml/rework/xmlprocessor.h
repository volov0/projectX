/**
 * @file xmlprocessor.h
 * @author Vaclav Koudelka
 * @brief XML processor class definition
 */

#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include <string>
#include <fstream>
#include <iostream>
#include <mutex>

/**
 * Class for filtering xml.
 */
class XMLProcessor {
private:
	std::ifstream file;              /**< XML file */
	bool terminated;                 /**< Filter termination flag */

	std::string ret_s;               /**< return string. Content is filtered */
	std::mutex ret_s_mutex;          /**< return string mutex */

	char shared_c;                   /**< input char shared across threads */
	std::mutex shared_c_empty_mutex; /**< input char mutex */
	std::mutex shared_c_full_mutex;  /**< input char mutex */

	//todo: std::map<std::string,bool> prohibited; /**< map of prohibited tags*/

public:
	/**
	 * Constructor 
	 */
	XMLProcessor(char *filename);
	/**
	 * Destructor 
	 */
	~XMLProcessor() { if (file.is_open()) { file.close(); }};

	/**
	 * Function member
	 * Launches threads.
	 */
	void run();

	/**
	 * Function member
	 * Reads input/writes output.
	 */
	void reader_writer(); 

	/**
	 * Function member
	 * Filter thread function.
	 */
	void process();

	/**
	 * Function member
	 * Terminate process() thread
	 */
	void terminate();

	/**
	 * Function member
	 * Print string to output
	 */
	void print_it() {
		std::lock_guard<std::mutex> lock(ret_s_mutex);
		if (ret_s.empty()) return;
		std::cout << ret_s;
		ret_s.clear();
	}
};
#endif /* XMLPROCESSOR_H */
