/**
 * @file   tuypecast.cpp
 * @author Vaclav Koudelka
 * @date   25.09.2015  
 * @brief  Konverze 
 * 
 *  Sample prirazovani hodnot do promennych ruznych typu.
 */


#include <iostream>
#include <typeinfo>

using namespace std;

class Hand {
private:
	int finger_count;
	string *ptr;
public:
	/* Default konstruktor*/
	Hand() : finger_count(5) { 
		ptr = new string("I am default Hand.");
		cout << "\t-class Hand- default constructor." << endl; 
	}

	/* Konstruktor z intu */
	Hand(int i) : finger_count(i) { 
		ptr = new string("I am default Hand.");
		cout << "\t-class Hand- int constructor." << endl; 
	} 

	/* Konstruktor ze stringu */
	Hand(string s) : finger_count(5) { 
		ptr = new string(s);
		cout << "\t-class Hand- string constructor." << endl; 
	} 

	/* Copy konstruktor */
	Hand(const Hand& x) { 
		finger_count = x.finger_count;
		ptr = new string(*x.ptr);
		cout << "\t-class Hand- copy constructor." << endl; 
	} 

	/* Move konstruktor */
	Hand(Hand&& x) :ptr(x.ptr) {  // && rvalue reference - pouziva se pro temporary objekty 
		finger_count = x.finger_count;
		x.ptr = NULL;
		cout << "\t-class Hand- copy constructor." << endl; 
	} 

	/* Destruktor */
	~Hand() {
		delete ptr;
		cout << "\t-class Hand- destruktor." << endl; 
	}

	/* Copy assignment */
	Hand& operator= (const Hand& x) {
		delete ptr;
		ptr = new string(*x.ptr);
		finger_count = x.finger_count;
		cout << "\t-class Hand- copy assignment." << endl; 
		return *this;
	}

	/* Move assignment */
	Hand& operator= (Hand&& x) {
		delete ptr;
		ptr = x.ptr;
		x.ptr = NULL;
		finger_count = x.finger_count;
		cout << "\t-class Hand- move assignment." << endl; 
		return *this;
	}

	void setcontent(string s) { *ptr = s; }

	int fcount() const { return finger_count; }
	void print() const { cout << "\t-class Hand- finger count: " << finger_count << ", content:" << *ptr << endl; }
};

class Foot {
private:
	int finger_count;
public:
	Foot(int i): finger_count(6) {}

	/* conversion operator from Hand to Foot */
	Foot& operator=(const Hand& x) {
		finger_count = x.fcount();
		cout << "\t-class Foot- conversion operator." << endl; 
		return *this;
	}

	/* Type-cast operator */
	explicit operator Hand() {
		cout << "\t-class Foot- type-cast." << endl; 
		//Hand x = finger_count;
		return Hand(finger_count);
	}
	int footfcount() { return finger_count; }
	void print() { cout << "\t-class Foot- finger count: " << finger_count << endl; }
};

/* vrati nejakou ruku */
Hand hand_factory() {
	Hand robotic_hand("Robotic hand");
	return robotic_hand;
}


/**
 * Function main
 * -------------
 * - test 01
*/
int main(int argc, char **argv) {
	/*  */
	Hand right_hand("Human right hand");   // string konstruktor
	Hand left_hand(right_hand);            // copy construktor

	left_hand.setcontent("Human left hand");

	/* Explicitni prirazeni */
	cout << "Right hand (typeid=" << typeid(right_hand).name() << "):" << endl;
	right_hand.print();
	cout << "Left hand: " << endl;
	left_hand.print();
	left_hand = right_hand;                // copy prirazeni
	cout << "Left hand after assign: " << endl;
	left_hand.print();
	cout << "--------------------" << endl;

	/* Dynamicka ruka */
	Hand *snake_hand;
	cout << "Snake hand: (typeid=" << typeid(snake_hand).name() << "):" << endl;
	snake_hand = new Hand("Snake hand.");
	snake_hand->print();
	delete snake_hand;
	cout << "--------------------" << endl;

	/* Move operator */
	cout << "Factory hand: " << endl;
	Hand hand_from_factory;
	hand_from_factory = hand_factory();
	//hand_from_factory = hand_from_factory + left_hand;   // pokud je operator+, tak tohle je taky move operator 
	hand_from_factory.print();
	cout << "--------------------" << endl;
	
	/* Konverze typu */
	cout << "Left foot: " << endl;
	Foot left_foot = 6;                    // int konstruktor
	left_foot.print();
	cout << "--- Conversion with operator= ----" << endl;
	left_foot = hand_from_factory;
	cout << "Left foot after conversion: " << endl;
	left_foot.print();
	cout << "--- Conversion with type-cast ----" << endl;
	right_hand = (Hand)left_foot;          // explicitni konverze je nutne protoze mam u type-cast operatoru "explicit"
	cout << "Right foot after type-cast: " << endl;
	right_hand.print();
	    
	    
	cout << "--------------------" << endl;

 	return 0;
}

