/**
 * @file   rxml.cpp
 * @author Vaclav Koudelka
 * @brief  XML parser with <thread>
 */

#include <iostream>      
#include <fstream>        
#include <queue>           
#include <thread>             
#include <condition_variable> 
#include <mutex>             

using namespace std;


condition_variable cv;
mutex cv_m;

int i = 0;

void thr1() {
	unique_lock<mutex> lk(cv_m);
	cout << "thr1 waiting..." << endl;
	cv.wait(lk, []{return i == 1;});

	cout << "thr1 finished waiting. i == 1." << endl;

	if (lk.owns_lock()) 
		cout << "thr1 - 1 - owns lock." << endl;
	else
		cout << "thr1 - 1 - does NOT owns lock." << endl;
	this_thread::sleep_for(chrono::seconds(2));
}
void thr2() {
	this_thread::sleep_for(chrono::seconds(1));
	cout << "thr2 notifying, but i == 0." << endl;
	cv.notify_one();

	this_thread::sleep_for(chrono::seconds(1));
	unique_lock<mutex> lk(cv_m);

	if (lk.owns_lock()) 
		cout << "thr2 - 1 - owns lock." << endl;
	else
		cout << "thr2 - 1 - does NOT owns lock." << endl;

	i = 1;
	lk.unlock();
	cout << "thr2 notify again, i == 1 this time." << endl;
	cv.notify_one();
	
	this_thread::sleep_for(chrono::seconds(2));

	if (lk.owns_lock()) 
		cout << "thr2 - 2 - owns lock." << endl;
	else
		cout << "thr2 - 2 - does NOT owns lock." << endl;

	cout << "thr2 done." << endl;

}
/**
 * Function main
 * -------------
 */
int main(int argc, char **argv) {

	thread t1(thr1), t2(thr2);
	t1.join();
	t2.join();

	return 0;
}
