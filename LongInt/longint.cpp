#include "longint.h"

// Constructor - Reads a string to convert to dequeue
LongInt::LongInt(const string & str)
{
	insertHelper(str);
}

// Copy Constructor
LongInt::LongInt(const LongInt & rhs)
{
	// Utilize operator=
	*this = rhs;
}

// Destructor
LongInt::~LongInt()
{
	sign = true;
	digits.clear();
}

// Arithmetic binary operator+
LongInt LongInt::operator+(const LongInt &rhs)
{
	LongInt result;
	// Positive lhs + Positive rhs
	if (this->sign == true && rhs.sign == true)
	{
		result.sign = true;
		if (*this < rhs)
			plus(result, *this, rhs, this->digits.size() - 1, rhs.digits.size() - 1);
		else
			plus(result, rhs, *this, rhs.digits.size() - 1, this->digits.size() - 1);
	}

	// Negative lhs + Negative rhs
	else if (this->sign == false && rhs.sign == false)
	{
		result.sign = false;
		if (*this > rhs)
			plus(result, *this, rhs, this->digits.size() - 1, rhs.digits.size() - 1);
		else
			plus(result, rhs, *this, rhs.digits.size() - 1, this->digits.size() - 1);
	}

	else 
	{
		LongInt a = *this;
		LongInt b = rhs;
		// Negative lhs + Positive rhs
		if (this->sign == false && rhs.sign == true)
		{
			a.sign = true;
			if (a <= b)
			{
				result = b - a;
				result.sign = true;
			}
			else
			{
				result = a - b;
				result.sign = false;
			}
		}
		// Positive Lhs + Negative Rhs
		else
		{
			b.sign = true;
			if (a < b)
			{
				result = b - a;
				result.sign = false;
			}
			else
			{
				result = a - b;
				result.sign = true;
			}
		}
	}
	return result;
}

// Binary operator+ helper
void LongInt::plus(LongInt & sum, const LongInt & a, const LongInt & b, int small, int large)
{
	int carry = 0;
	while (small >= 0)
	{
		sum.digits.push_front(((a.digits[small] - '0') + (b.digits[large] - '0')
								+ carry) % 10 + '0');
		carry = ((a.digits[small--] - '0') + (b.digits[large--] - '0')
			    + carry) / 10;
	}

	for (int i = 0; i <= large; i++)
	{
		sum.digits.push_front((b.digits[large] - '0' + carry) % 10 + '0');
		carry = (b.digits[large] - '0' + carry) / 10;
	}

	if (carry != 0)
		sum.digits.push_front(carry + '0');
}

// Arithmetic binary operator-
LongInt LongInt::operator-(const LongInt &rhs)
{
	LongInt result, a = *this, b = rhs;

	// Positive Lhs - Negative Rhs
	if (a.sign == true && b.sign == false)
	{
		b.sign = true;
		return a + b;
	}
	// Negative Lhs - Positive Rhs
	else if (a.sign == false && b.sign == true)
	{
		b.sign = false;
		return a + b;
	}
	// Negative Lhs - Negative Rhs
	else if (a.sign == false && b.sign == false)
	{
		a.sign = true, b.sign = true;
		if (a < b)
		{
			minus(result, b, a, a.digits.size() - 1, b.digits.size() - 1);
			result.sign = true;
		}
		else if (a > b)
		{
			minus(result, a, b, b.digits.size() - 1, a.digits.size() - 1);
			result.sign = false;
		}
		else
		{
			result.digits.push_back(0 + '0');
			result.sign = true;
		}
	}
	// Positive Lhs - Positive Rhs
	else if (a.sign == true && b.sign == true)
	{
		if (a > b)
		{
			minus(result, a, b, b.digits.size() - 1, a.digits.size() - 1);
			result.sign = true;
		}
		else if (a < b)
		{
			minus(result, b, a, a.digits.size() - 1, b.digits.size() - 1);
			result.sign = false;
		}
		else
		{
			result.digits.push_back(0 + '0');
			result.sign = true;
		}
	}
	return result;
}

// Binary operator- helper
void LongInt::minus(LongInt & result, LongInt & a, LongInt & b, int small, int large)
{
	while (small >= 0)
	{
		if (a.digits[large] - '0' < b.digits[small] - '0')
		{
			// Out of bound check
			if (large > 0)
			{
				a.digits[large - 1] = a.digits[large - 1] - 1;
				int borrow = large - 1;
				while (a.digits[borrow] - '0' < 0)
				{
					// Borrow 
					a.digits[borrow - 1] = a.digits[borrow - 1] - 1;
					a.digits[borrow] = a.digits[borrow--] + 10;
				}
				result.digits.push_front((a.digits[large] - '0' + 10) - (b.digits[small] - '0') + '0');
			}
			else
				result.digits.push_front((b.digits[small] - '0') + '0');
		}
		else if (a.digits[large] - '0' >= b.digits[small] - '0')
			result.digits.push_front((a.digits[large] - '0') - (b.digits[small] - '0') + '0');
		else if (a.digits[small] > 0)
				result.digits.push_front(0 + '0');
		small--;
		large--;
	}

	for (int i = 0; i <= large; i++)
	{
		if (a.digits[i] - '0' != 0)
			result.digits.push_front(a.digits[i]);
	}

	// Remove extra 0's
	while (result.digits[0] - '0' == 0)
		result.digits.pop_front();
}

// Assignment operator=
const LongInt& LongInt::operator=(const LongInt &rhs)
{
	this->digits = rhs.digits;
	this->sign = rhs.sign;
	return *this;
}

// Logical Binary Operator for (*this < rhs)
bool LongInt::operator<(const LongInt & rhs) const
{
	bool cond = false;
	int sizeLHS = this->digits.size();
	int sizeRHS = rhs.digits.size();
	bool lhsSign = this->sign;
	bool rhsSign = rhs.sign;
	// If their signs are different, the operand 
	// with a negative sign is a smaller integer
	if (lhsSign == false && rhsSign == true)
		cond = true;
	// If the signs are both positive 
	// but their sizes are different
	else if (lhsSign == true && rhsSign == true && sizeLHS < sizeRHS)
		cond = true;
	// If the signs are both negative, the operand 
	// with a larger deque size is a smaller integer
	else if (lhsSign == false && rhsSign == false && sizeLHS > sizeRHS)
		cond = true;
	// Compare each element
	else if (lhsSign == rhsSign && sizeLHS == sizeRHS)
	{
		for (int i = 0; i < sizeLHS; i++)
		{
			if (this->digits[i] - '0' != rhs.digits[i] - '0')
			{
				if ((this->digits[i] - '0' > rhs.digits[i] - '0' && rhsSign == false) ||
					(this->digits[i] - '0' < rhs.digits[i] - '0' && rhsSign == true))
					return true;
				else
					return false;

			}
		}
	}
	return cond;
}

// Logical Binary Operator for (*this <= rhs)
bool LongInt::operator<=(const LongInt & rhs) const
{
	return (*this < rhs) || (*this == rhs);
}

// Logical Binary Operator for (*this > rhs)
bool LongInt::operator>(const LongInt & rhs) const
{
	return rhs < *this;
}

// Logical Binary Operator for (*this >= rhs)
bool LongInt::operator>=(const LongInt & rhs) const
{
	return (*this > rhs) || (*this == rhs);
}

// Logical Binary Operator for (*this == rhs)
bool LongInt::operator==(const LongInt & rhs) const
{
	// Compare the sign
	if (this->sign != rhs.sign)
		return false;
	// Compare the size
	else if (this->digits.size() != rhs.digits.size())
		return false;
	// Compare each element
	else if (this->digits.size() == rhs.digits.size() && this->sign == rhs.sign)
	{
		for (unsigned int i = 0; i < this->digits.size(); i++)
		{
			if (this->digits[i] != rhs.digits[i])
				return false;
		}
	}
	return true;
}

// Logical Binary Operator for (*this != rhs)
bool LongInt::operator!=(const LongInt & rhs) const
{
	return !(rhs == *this);
}

// Read long integer
istream &operator>>(istream &in, LongInt &rhs)
{
	string str;
	in >> str;
	rhs.insertHelper(str);
	return in;
}

// Helper function for operator>>
void LongInt::insertHelper(const string & str)
{
	unsigned int i = 0;
	this->sign = true;
	if (str[0] == '-')
	{
		i++;
		this->sign = false;
	}
	
	// Ignore extra 0's
	while (str[i] == '0')
		i++;

	while(i < str.length())
	{
		// Store integers '0' through '9'
		if (str[i] >= 48 && str[i] <= 57)
			this->digits.push_back(str[i]);
		i++;
	}
}

// Display long integer
ostream &operator<<(ostream &out, const LongInt &rhs)
{
	if (rhs.sign == false)
		cout << "-";
	deque<char>::const_iterator i;
	for (i = rhs.digits.begin(); i != rhs.digits.end(); i++)
		out << *i;
	return out;
}
