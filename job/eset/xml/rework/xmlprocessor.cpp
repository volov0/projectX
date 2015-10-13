/**
 * @file xmlprocessor.cpp
 * @author Vaclav Koudelka
 * @brief XML processor class implementation
 */

#include "xmlprocessor.h"
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <map>
#include <algorithm>


XMLProcessor::XMLProcessor(char *filename) : terminated(false) {
	/* Open input file */
	file.open(filename);
	if (!file.is_open()) {
		std::cout << "Can't open file." << std::endl;
		exit(2);
	}

	/* Init lock state */
	shared_c_full_mutex.lock();
	
	/* init prohibited tag set */
	prohibited.insert(std::make_pair("img", 0));
	prohibited.insert(std::make_pair("object", 0));
	prohibited.insert(std::make_pair("script", 0));
}

void XMLProcessor::run() {
	/* Run threads */
	std::thread t1(&XMLProcessor::reader_writer, this);
	std::thread t2(&XMLProcessor::filter, this);

	/* Collect threads */
	t1.join();
	t2.join();
}

void XMLProcessor::reader_writer() {
	char c;

	while(file.get(c)) {
		/* Wait for filter() to process char */
		shared_c_empty_mutex.lock();

		shared_c = c;

		/* Signal filter() that char is ready to process */
		shared_c_full_mutex.unlock();

		/* Print output */
		print_it();
	}

	/* Say file is processed */
	terminate();

	/* Print last output */
	print_it();
}

void XMLProcessor::filter() {
	char c;
	bool in_tag = false;       // says that processing is inside <,> brackets
	std::string buffer;        // working buffer - usually contains tag which is currently processed
	std::string tag;           // work tag name

	while(1) {
		/* Wait till input is ready or filter is terminated */
		shared_c_full_mutex.lock();

		c = shared_c;

		/* tell writer that input is processed */
		shared_c_empty_mutex.unlock();

		/* get out of the loop whe Filter is terminated */
		if (terminated) break;

		/* process input char */
		if (in_tag) {
			buffer += c;
			if (c == '>') {
				/* process buffer - it contains complete tag at this point */
				if (end_of_prohibited_tag(buffer, tag)) {
					if (in_prohibited()) {
						/* decrease nesting level of prohibited tag */
						if (prohibited[tag] > 0) --prohibited[tag];
					}
				}
				else if (start_of_prohibited_tag(buffer, tag)) {
					/* check for single tag */
					if (buffer[buffer.size() - 2] != '/') {
						/* increase nesting level of prohibited tag */
						++prohibited[tag];
					}
				}
				else if (!in_prohibited()){
					/* buffer contains allowed tag so append it to return string */
					ret_s_mutex.lock();
					ret_s += buffer;
					ret_s_mutex.unlock();
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
			else if (!in_prohibited()) {
				/* c is simple character - append it to return string */
				ret_s_mutex.lock();
				ret_s += c;
				ret_s_mutex.unlock();
			}
		}

	}
}

void XMLProcessor::terminate() {
	terminated = true;
	/* Signal filter() that char reading is finished */
	shared_c_full_mutex.unlock();
}

bool XMLProcessor::end_of_prohibited_tag(const std::string& s, std::string& tagname) const {
	//* sanity check */
	if ((s.length() <= 4) || (s.substr(0,2) != "</") || (s[s.length() - 1] != '>'))
		return false;
	
	/* check if tag name is in prohibited set */
	tagname = s.substr(2, s.length() - 3); 
	std::transform(tagname.begin(), tagname.end(), tagname.begin(), tolower);
	return prohibited.count(tagname);  
}

bool XMLProcessor::start_of_prohibited_tag(const std::string& s, std::string& tagname) const {
	//* sanity check */
	if ((s.length() <= 3) || (s[0] != '<') || (s[s.length() - 1] != '>'))
		return false;
	
	/* check if tag name is in prohibited set */
	std::string nonalpha(" \t\f\v\n\r/>");
	tagname = s.substr(1, s.find_first_of(nonalpha, 1) - 1);
	std::transform(tagname.begin(), tagname.end(), tagname.begin(), tolower);
	return prohibited.count(tagname);  
}

bool XMLProcessor::in_prohibited() const {
	int sum = 0;

	std::map<std::string, int>::const_iterator it;
	for (it = prohibited.begin(); it != prohibited.end(); ++it) {
		sum += it->second;
	}

	return (sum > 0);
}

