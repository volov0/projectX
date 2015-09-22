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

using namespace std;

void reader_writer(ifstream& file, asynch_queue<char>& inq, asynch_queue<char>& outq);
void tag_filter(asynch_queue<char>& inq, asynch_queue<char>& outq); 
void printer(asynch_queue<char>& q);
bool start_of_prohibited_tag(const std::string& s, std::string& tag); 
bool end_of_prohibited_tag(const std::string& s, const std::string& tag); 



/**
 * Function main
 * -------------
 */
int main(int argc, char **argv) {
	ifstream myfile;
	asynch_queue<char> inbuffer;
	asynch_queue<char> outbuffer;

	myfile.open("index.xml");
	if (!myfile.is_open()) {
		cout << "Can't open file." << endl;
		exit(0);
	}

	thread t1(reader_writer, ref(myfile), ref(inbuffer), ref(outbuffer));
	thread t2(tag_filter, ref(inbuffer), ref(outbuffer));
	// todo: join xml filter
	t1.join();
	t2.join();
	//thread t3(printer, ref(outbuffer));

	myfile.close();


	return 0;
}

/**
 * Function reader_writer
 * ----------------------
 */
void reader_writer(ifstream& file, asynch_queue<char>& inq, asynch_queue<char>& outq) {
	char c;
	this_thread::sleep_for(chrono::milliseconds(10));

	while (file.get(c)) {
		/* add to input buffer */
		inq.push(c);

		//this_thread::sleep_for(chrono::milliseconds(12));

		/* try read from output buffer */
		while (outq.try_pop(c)) {
			cout << c;
		}
	}

	// say file is processed
	inq.terminate();

	/* read last chunk from output buffer */
	cout << "rw flush outq" << endl;
	while (outq.pop(c)) {
		cout << c;
	}
	cout << "rw flush DONE" << endl;
}

/**
 * Function tag_filter
 * -------------------
 */
void tag_filter(asynch_queue<char>& inq, asynch_queue<char>& outq) {
	char c; 
	bool in_tag = false, in_proh = false;
	string buffer, start_tag;

	while(inq.pop(c)) { 
		//this_thread::sleep_for(chrono::milliseconds(10));

		/* process character */

		if (in_tag) {
			buffer += c;
			if (c == '>') {
				// process buffer
				if (in_proh) {
					if (end_of_prohibited_tag(buffer, start_tag)) {
						in_proh = false;
					}
				}
				//cout << "tw >>>> " << buffer << endl;
				else if (start_of_prohibited_tag(buffer, start_tag)) {
					if (buffer[buffer.size() - 2] != '/') {   // single terminated tag
						in_proh = true;
						cerr << "tw start of proh " << buffer << endl;
					}
				}
				else {
					for (unsigned i = 0; i < buffer.size(); i++)
						outq.push(buffer[i]); 
				}
				buffer.clear();
				in_tag = false;
			}
		}
		else {
			/* put result to the output buffer */
			if (c == '<') {
				in_tag = true;
				buffer += c;
			}
			else if (!in_proh) {
				outq.push(c);
			}
		}

	}
	
	/* say filtering is done */
	cout << "tw terminate" << endl;
	outq.terminate();
}

bool end_of_prohibited_tag(const std::string& s, const std::string& tag) {
	std::string cs;
	cs = "</>" + tag + ">";
	cerr << "EOPT testing " << s << " tag: " << tag << "res: " << (s == cs) << endl;
	return (s == cs);
}
bool start_of_prohibited_tag(const std::string& s, std::string& tag) {
	std::smatch sm;
	std::regex e("<(img|object|script).*>");   // buggy in g++
	cerr << "SOPT testing " << s;
	if (std::regex_match(s, sm, e)) {
		tag = sm[1];
		cerr << " TRUE - " << sm[1] << endl;
		return true;
	}
	else {
		cerr << " FALSE" << endl;
		return false;
	}
}

/**
 * Function printer
 * ----------------
 */
void printer(asynch_queue<char>& q) {
	char c;
	while (q.pop(c)) {
		cout  << c;
	}
}
