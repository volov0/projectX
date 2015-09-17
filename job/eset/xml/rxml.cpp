/**
 * @file   rxml.cpp
 * @author Vaclav Koudelka
 * @brief  XML parser with <thread>
 */

#include <iostream>         // std::cout
#include <fstream>          // std::file
#include <queue>            // std::queue
#include <thread>           // std::thread
#include <mutex>            // std::mutex

using namespace std;

void reader_writer(ifstream& file, queue<char>& inq);
void tag_filter(queue<char>& inq, queue<char>& outq); 
void printer(queue<char>& q); 

mutex iq_mutex;
mutex oq_mutex;
queue<char> inbuffer;
queue<char> outbuffer;

/**
 * Function main
 * -------------
 */
int main(int argc, char **argv) {
	ifstream myfile;

	myfile.open("index.xml");
	if (!myfile.is_open()) {
		cout << "Can't open file." << endl;
		exit(0);
	}

	reader_writer(myfile, inbuffer);
	// todo: join xml filter
	// todo: vyprazdni a cti outbuffer
	tag_filter(inbuffer, outbuffer);
	printer(outbuffer);

	myfile.close();


	return 0;
}

/**
 * Function reader_writer
 * ----------------------
 */
void reader_writer(ifstream& file, queue<char>& inq) {
	char c;

	while (file.get(c)) {
		iq_mutex.lock();
		inq.push(c);
		iq_mutex.unlock();

		// todo: cti z outbufferu
	}
}

/**
 * Function tag_filter
 * -------------------
 */
void tag_filter(queue<char>& inq, queue<char>& outq) {
	char c; 

	while(!inq.empty()) {
		iq_mutex.lock();
		c = inq.front();
		inq.pop();
		iq_mutex.unlock();

		if (c == '<' || c == '>')
			c = '#';

		oq_mutex.lock();
		outq.push(c);
		oq_mutex.unlock();
	}
}

/**
 * Function printer
 * ----------------
 */
void printer(queue<char>& q) {
	while (!q.empty()) {
		oq_mutex.lock();
		cout  << q.front();
		q.pop();
		oq_mutex.unlock();
	}
}
