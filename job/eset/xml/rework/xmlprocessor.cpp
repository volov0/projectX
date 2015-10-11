/**
 * @file xmlprocessor.cpp
 * @author Vaclav Koudelka
 * @brief XML processor class implementation
 */

#include "xmlprocessor.h"
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

/* todo */
bool start_of_prohibited_tag(const std::string& s, std::string& tag);
bool end_of_prohibited_tag(const std::string& s, const std::string& tag);

XMLProcessor::XMLProcessor(char *filename) {
	/* Open input file */
	file.open(filename);
	if (!file.is_open()) {
		std::cout << "Can't open file." << std::endl;
		exit(2);
	}

	terminated = false;

	/* Init lock state */
	shared_c_full_mutex.lock();
	//ret_s_full_mutex.lock();
}

void XMLProcessor::run() {
	/* Run threads */
	std::thread t1(&XMLProcessor::reader_writer, this);
	std::thread t2(&XMLProcessor::process, this);

	/* Collect threads */
	t1.join();
	t2.join();
}

void XMLProcessor::reader_writer() {
	char c;

	while(file.get(c)) {
		/* Wait for process() to process char */
		shared_c_empty_mutex.lock();

		shared_c = c;
		//std::cout << "rw: shared_c set as " << c << std::endl;

		/* Signal process() that char is ready to process */
		shared_c_full_mutex.unlock();

		/* Print output */
		print_it();
	}

	/* Say file is processed */
	terminate();

	/* Print last output */
	print_it();
}

void XMLProcessor::process() {
	char c;
	bool in_tag = false;       // says that processing is inside <,> brackets
	int in_proh = 0;           // nesting level of prohibited tag
	std::string buffer;        // working buffer - usually contains tag which is currently processed
	std::string start_tag;     // if processing is "in_proh" state it contains name of prohibited tag

	while(1) {
		/* Wait till input is ready or filter is terminated */
		//sem_wait(full);
		shared_c_full_mutex.lock();

		c = shared_c;
		//std::cout << "pr: shared_c get as " << c << std::endl;

		/* tell writer that input is processed */
		//sem_post(empty);
		shared_c_empty_mutex.unlock();

		/* get out of the loop whe Filter is terminated */
		if (terminated) break;

		/* process input char */
		if (in_tag) {
			buffer += c;
			if (c == '>') {
				/* process buffer - it contains complete tag at this point */
				if (end_of_prohibited_tag(buffer, start_tag)) {
					if (in_proh > 0) {
						/* decrease nesting level of prohibited tag */
						--in_proh;
					}
				}
				else if (start_of_prohibited_tag(buffer, start_tag)) {
					/* check for single tag */
					if (buffer[buffer.size() - 2] != '/') {
						/* increase nesting level of prohibited tag */
						++in_proh;
					}
				}
				else if (in_proh == 0){
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
			else if (in_proh == 0) {
				/* c is simple character - append it to return string */
				ret_s_mutex.lock();
				ret_s += c;
				ret_s_mutex.unlock();
			}
		}

	}
	std::cout << "Filter process() done." << std::endl;

}

void XMLProcessor::terminate() {
	terminated = true;
	/* Signal process() that char reading is finished */
	shared_c_full_mutex.unlock();
	std::cout << "Filter terminate()" << std::endl;
}

/* todo */
/**
 * Determines if tag is terminate tag of "prohibited" tag
 * @param st which contains complete content of parsed tag including <,> brackets
 * @param tag_name contains name of "prohibited" tag
 * @return true if input tag is found to be terminating "prohibited" tag
 */
bool end_of_prohibited_tag(const std::string& s, const std::string& tag_name) {
	std::vector<std::string> prohibited = {"img", "object", "script"};
	std::string cs;

	/* sanity check */
	if ((s.length() <= 4) || (s.substr(0,2) != "</"))
		return false;
	
	/* compare tag name with prohibited tags */
	cs = s.substr(2, s.length() - 3);         //contains tag name only 
	for (unsigned i = 0; i < prohibited.size(); i++) {
		if (cs.compare(prohibited[i]) == 0) {
			return true;
		}
	}
	return false;
}

/**
* Determines if tag is "prohibited"
* @param st which contains complete content of parsed tag including <,> brackets
* @param tag_name if returns true then simple name of prohibited tag is set
* @return true if input tag is found prohibited
*/
bool start_of_prohibited_tag(const std::string& st, std::string& tag_name) {
	std::vector<std::string> prohibited = {"img", "object", "script"};
	std::string nonalpha(" \t\f\v\n\r/>");
	size_t end_of_tagname;
	
	end_of_tagname = st.find_first_of(nonalpha, 1) - 1;
	tag_name = st.substr(1, end_of_tagname);
	std::transform(tag_name.begin(), tag_name.end(), tag_name.begin(), tolower);
	for (unsigned i = 0; i < prohibited.size(); i++) {
		if (tag_name.compare(prohibited[i]) == 0) {
			return true;
		}
	}
	return false;
}


