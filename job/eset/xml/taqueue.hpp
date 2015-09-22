/**
 * @file   taqueue.hpp
 * @brief  Asynchronous queue
 */

#ifndef TAQUEUE_HPP
#define TAQUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

/**
 * Template for queue with concurrent access and mechanism to handle
 * end of processing.
 */
template<typename T>
class asynch_queue
{
private:
	queue<T> q; 
	mutex cv_m;            
	condition_variable cv;
	bool processing_done;
public:
	/**
	 * Constructor.
	 */
	asynch_queue() { processing_done = false; }

	/**
	 * Push element to a queue.
	 * @param v value to be pushed to a queue
	 */
	void push(T const& v) {
		unique_lock<mutex> lk(cv_m);
		q.push(v);
		//lk.unlock();
		cv.notify_one();
	}
	
	/*void push(vector<T> const& vect) {
		unique_lock<mutex> lk(cv_m);
		for (int i = 0; i < vect.size(); i++)
			q.push(vect[i]);
		//lk.unlock();
		cv.notify_one();
	}*/

	/**
	 * Pop element from a queue. 
	 * If queue is empty then wait until new element is pushed or
	 * until queue is terminated.
	 * @param v after return will contain poped element
	 * @return true if element was poped, false if queue is empty and terminated
	 */
	bool pop (T& v) {
		unique_lock<mutex> lk(cv_m);
		while (q.empty() && !processing_done) {    // avoid spurious wakeup
			cv.wait(lk);
		}

		if (q.empty())
			return false;

		v = q.front();
		q.pop();
		//lk.unlock();
		return true;
	}

	/**
	 * Try to pop element from a queue. 
	 * If queue is empty simply return false.
	 * @param v after return will contain poped element
	 * @return true if element was poped, false if queue is empty
	 */
	bool try_pop (T& v) {
		unique_lock<mutex> lk(cv_m);
		if (q.empty())
			return false;

		v = q.front();
		q.pop();
		//lk.unlock();
		return true;
	}

	/**
	 * Mark end of queue processing.
	 * Simply put after terminate call it is not allow to push anymore.
	 */
	void terminate() {
		unique_lock<mutex> lk(cv_m);
		processing_done = true;
		//lk.unlock();
		cv.notify_one();
	}
};

#endif  /* TAQUEUE_HPP */
