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
#include <map>

/**
 * Class for filtering xml.
 */
class XMLProcessor {
private:
	std::ifstream file;               /**< XML file */
	bool terminated;                  /**< Filter termination flag */

	std::string ret_s;                /**< return string. Content is filtered */
	std::mutex ret_s_mutex;           /**< return string mutex */

	char shared_c;                    /**< input char shared across threads */
	std::mutex shared_c_empty_mutex;  /**< input char mutex */
	std::mutex shared_c_full_mutex;   /**< input char mutex */

	std::map<std::string, int> prohibited; /**< map of prohibited tags*/

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
	 * Launches threads.
	 */
	void run();

private:
	/**
	 * Reads input/writes output.
	 */
	void reader_writer(); 

	/**
	 * Filter thread function.
	 */
	void filter();

	/**
	 * Terminate filter() thread
	 */
	void terminate();

	/**
	 * Print string to output
	 */
	void print_it() {
		std::lock_guard<std::mutex> lock(ret_s_mutex);
		if (ret_s.empty()) return;
		std::cout << ret_s;
		ret_s.clear();
	}

	/**
	 * Determines if tag is terminate "prohibited" tag
	 * @param s which contains complete content of parsed tag including <,> brackets
	 * @param tagname  simple plain text name of tag is set
	 * @return true if input tag is found to be terminating "prohibited" tag
	 */
	bool end_of_prohibited_tag(const std::string& s, std::string& tagname);

	/**
	 * Determines if tag is "prohibited"
	 * @param s which contains complete content of parsed tag including <,> brackets
	 * @param tagname true simple plain text name of tag is set
	 * @return true if input tag is found prohibited
	 */
	 bool start_of_prohibited_tag(const std::string& s, std::string& tagname);

	/**
	 * Determines if filter processing is currently inside of "prohibited" tag
	 * @return true if processing is inside "prohibited" tag
	 */
	 bool in_prohibited();
};
#endif /* XMLPROCESSOR_H */
