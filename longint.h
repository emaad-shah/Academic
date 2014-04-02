#ifndef LONGINT_H
#define LONGINT_H
#include <iostream>
#include <string>
#include <deque>

using namespace std;

class LongInt 
{
	// Read store long integer
	friend istream &operator>>(istream &, LongInt &);
	// Display long integer
	friend ostream &operator<<(ostream &, const LongInt &);

	public:
		// Default Constructor
		LongInt() {};
		// Constructor - Reads a string to convert to dequeue
		LongInt(const string &);
		// Copy Constructor
		LongInt(const LongInt &);
		// Destructor
		~LongInt();
		// Arithmetic binary operator+
		LongInt operator+(const LongInt &);
		// Binary operator+ helper
		void plus(LongInt &, const LongInt &, const LongInt &, int, int);
		// Arithmetic binary operator-
		LongInt operator-(const LongInt &);
		// Binary operator- helper
		void minus(LongInt &, LongInt &, LongInt &, int, int);
		// Assignment operator=
		const LongInt &operator=(const LongInt &);
		// Helper function for operator>>
		void insertHelper(const string &);
		// Logical Binary Operator for (*this < rhs)
		bool operator< (const LongInt &)const;
		// Logical Binary Operator for (*this <= rhs)
		bool operator<=(const LongInt &)const;
		// Logical Binary Operator for (*this > rhs)
		bool operator> (const LongInt &)const;
		// Logical Binary Operator for (*this >= rhs)
		bool operator>=(const LongInt &) const;
		// Logical Binary Operator for (*this == rhs)
		bool operator==(const LongInt &) const;
		// Logical Binary Operator for (*this != rhs)
		bool operator!=(const LongInt &) const;

	private:
		// Facilitate very long integers
		deque<char> digits;
		// Indicates a signs of the long integer
		bool sign;
};

#endif
