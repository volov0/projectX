/**
 * @file   rxml.cpp
 * @author Vaclav Koudelka
 * @brief  XML parser with <thread>
 */

#include <iostream>      
#include <fstream>        
#include <thread>             
#include <regex>             
#include "taqueue.hpp"       

void reader_writer(std::ifstream& file, asynch_queue<char>& inq, asynch_queue<char>& outq);
void tag_filter(asynch_queue<char>& inq, asynch_queue<char>& outq);
bool start_of_prohibited_tag(const std::string& s, std::string& tag);
bool end_of_prohibited_tag(const std::string& s, const std::string& tag);

/**
 * Opens file and runs thread to process file.
 */
int main(int argc, char **argv) {
	std::ifstream myfile;
	asynch_queue<char> inbuffer;
	asynch_queue<char> outbuffer;

	/* read argument */
	if (argc == 1) {
		std::cerr << "You need to specify file." << std::endl;
		return 1;
	}

	/* open input file */
	myfile.open(argv[1]);
	if (!myfile.is_open()) {
		std::cout << "Can't open file." << std::endl;
		return 2;
	}

	/* init working threads */
	std::thread t1(reader_writer, std::ref(myfile), std::ref(inbuffer), std::ref(outbuffer));
	std::thread t2(tag_filter, std::ref(inbuffer), std::ref(outbuffer));
	//std::thread t3(printer, std::ref(outbuffer));

	/* collect threads */
	t1.join();
	t2.join();
	//t3.join();

	myfile.close();

	return 0;
}

/**
 * Reads input queue and places filtered text into ouptut queue
 * @param file opened file with xml input
 * @param inq input queue to be populated with xml from input file
 * @param outq output queue containg filtered xml which needs to be printed
 */
void reader_writer(std::ifstream& file, asynch_queue<char>& inq, asynch_queue<char>& outq) {
	char c;

	while (file.get(c)) {
		/* add to input buffer */
		inq.push(c);

		/* try read from output buffer */
		while (outq.try_pop(c)) {
			std::cout << c;
		}
	}

	/* say file is processed */
	inq.terminate();

	/* read last chunk from output buffer */
	while (outq.pop(c)) {
		std::cout << c;
	}
}

/**
 * Reads input queue and places filtered text into ouptut queue
 * @param inq input queue containg xml
 * @param outq output queue containg filtered xml
*/
void tag_filter(asynch_queue<char>& inq, asynch_queue<char>& outq) {
	char c;
	bool in_tag = false;       // says that processing is inside <,> brackets
	bool in_proh = false;      // says that processing is inside of text which should not be printed
	std::string buffer;        // working buffer - usually contains tag which is currently processed
	std::string start_tag;     // if processing is "in_proh" state it contains name of prohibited tag

	/* process characters from queue one by one */
	while (inq.pop(c)) {
		if (in_tag) {
			buffer += c;
			if (c == '>') {
				/* process buffer - it contains complete tag at this point */
				if (in_proh) {
					if (end_of_prohibited_tag(buffer, start_tag)) {
						/* say we are out of "prohibited" mode - means output can be printed */
						in_proh = false;
					}
				}
				else if (start_of_prohibited_tag(buffer, start_tag)) {
					/* check for single tag */
					if (buffer[buffer.size() - 2] != '/') {
						/* say we are in "prohibited" mode - means output is not printed */
						in_proh = true;
					}
				}
				else {
					/* buffer allowed tag so print it */
					for (unsigned i = 0; i < buffer.size(); i++)
						outq.push(buffer[i]);
				}
				/* clear buffer for next tag */
				buffer.clear();
				in_tag = false;
			}
		}
		else {
			if (c == '<') {
				/* tag start encountered - let's put it to buffer to see if it is allowed */
				in_tag = true;
				buffer += c;
			}
			else if (!in_proh) {
				/* c is simple character - put it to the output buffer */
				outq.push(c);
			}
		}
	}

	/* say filtering is done */
	outq.terminate();
}

/**
 * Determines if tag is terminate tag of "prohibited" tag
 * @param st which contains complete content of parsed tag including <,> brackets
 * @param tag_name contains name of "prohibited" tag
 * @return true if input tag is found to be terminating "prohibited" tag
 */
bool end_of_prohibited_tag(const std::string& s, const std::string& tag_name) {
	std::string cs("</" + tag_name + ">");
	return (s == cs);
}

/**
* Determines if tag is "prohibited"
* @param st which contains complete content of parsed tag including <,> brackets
* @param tag_name if returns true then simple name of prohibited tag is set
* @return true if input tag is found prohibited
*/
bool start_of_prohibited_tag(const std::string& st, std::string& tag_name) {
	std::smatch sm;
	std::regex e("<(img|object|script).*>");   // buggy in gcc
	if (std::regex_match(st, sm, e)) {
		tag_name = sm[1];
		return true;
	}
	else {
		return false;
	}
}

/**
 * printer
 */
void printer(asynch_queue<char>& q) {
	char c;
	while (q.pop(c)) {
		std::cout << c;	
	}
}
