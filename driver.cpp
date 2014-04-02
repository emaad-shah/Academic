//------------------------------------------------------------
// Copyright: Syed Emaad Shah 2014 
// Compiler: Visual Studio Express 2013
// 
// Some real-world applications such as public/private-key 
// cryptography need to use integers more than 100 digits  
// long. Those integer values are obviously not maintained in  
// C++ int variables. The LongInt class maintains a very long 
// integer with a Deque of charaters, (i.e., chars). In other
// words, each char-type item in Deque represents a different
// digit of a given integer; the front item corresponds to the
// most significant digit; and the tail item maintains the 
// least significant digit.
//------------------------------------------------------------

#include "longint.h"
#include <time.h>

int main(void)
{
	char choice;
	
	while (true)
	{
		cout << "Automated or Manual Testing. (a/m) ? ";
		cin >> choice;
		cout << endl;
		// Automated Testing
		if (toupper(choice) == 'A')
		{
			srand(time(NULL));

			int r1 = rand() % 200 - 100;
			int r2 = rand() % 200 - 100;
			LongInt a(to_string(r1));
			LongInt b(to_string(r2));
			if (r1 < r2 == a < b)
				cout << "Operator< functioning" << endl;
			else
				cout << "Operator< not functioning" << endl;
			cout << a << " + " << b << " = ";
			cout << a + b << " (Actual: " << r1 + r2 << ")" << endl;

			r1 = rand() % 200 - 100;
			r2 = rand() % 200 - 100;
			LongInt c(to_string(r1));
			LongInt d(to_string(r2));
			if (r1 > r2 == c > d)
				cout << "Operator> functioning" << endl;
			else
				cout << "Operator> not functioning" << endl;
			cout << c << " + " << d << " = ";
			cout << c + d << " (Actual: " << r1 + r2 << ")" << endl;

			r1 = rand() % 200 - 100;
			r2 = rand() % 200 - 100;
			LongInt e(to_string(r1));
			LongInt f(to_string(r2));
			if (r1 <= r2 == e <= f)
				cout << "Operator<= functioning" << endl;
			else
				cout << "Operator<= not functioning" << endl;
			cout << e << " + " << f << " = ";
			cout << e + f << " (Actual: " << r1 + r2 << ")" << endl;

			r1 = rand() % 200 - 100;
			r2 = rand() % 200 - 100;
			LongInt g(to_string(r1));
			LongInt h(to_string(r2));
			if (r1 >= r2 == g >= h)
				cout << "Operator>= functioning" << endl;
			else
				cout << "Operator>= not functioning" << endl;
			cout << g << " - " << h << " = ";
			cout << g - h << " (Actual: " << r1 - r2 << ")" << endl;

			r1 = rand() % 200 - 100;
			r2 = rand() % 200 - 100;
			LongInt i(to_string(r1));
			LongInt j(to_string(r2));
			if ((r1 == r2) == (i == j))
				cout << "Operator== functioning" << endl;
			else
				cout << "Operator== not functioning" << endl;
			cout << i << " - " << j << " = ";
			cout << i - j << " (Actual: " << r1 - r2 << ")" << endl;

			r1 = rand() % 200 - 100;
			r2 = rand() % 200 - 100;
			LongInt k(to_string(r1));
			LongInt l(to_string(r2));
			if ((r1 != r2) == (k != l))
				cout << "Operator!= functioning" << endl;
			else
				cout << "Operator!= not functioning" << endl;
			cout << k << " - " << l << " = ";
			cout << k - l << " (Actual: " << r1 - r2 << ")" << endl;
			break;
		}

		else if (toupper(choice) == 'M')
		{
			LongInt a, b, c, d, e("-0099999999999999999999999999999999x");
			cout << "Enter for a: ";
			cin >> a;
			cout << "Enter for b: ";
			cin >> b;
			cout << "Enter for c: ";
			cin >> c;
			cout << "Enter for d: ";
			cin >> d;
			cout << "a = " << a << endl;
			cout << "b = " << b << endl;
			cout << "c = " << c << endl;
			cout << "d = " << d << endl;
			cout << "e = " << e << endl;

			LongInt f = e;
			cout << "f = " << f << endl;

			cout << a << " + " << b << " =  " << (a + b) << endl;
			cout << a << " - " << b << " =  " << (a - b) << endl;
			cout << b << " - " << a << " =  " << (b - a) << endl;
			cout << b << " + " << a << " =  " << (b + a) << endl;
			cout << a << " == " << c << " =  " << (a == c) << endl;
			cout << a << " != " << c << " =  " << (a != c) << endl;
			cout << a << " > " << d << " =  " << (a > d) << endl;
			cout << a << " >= " << d << " =  " << (a >= d) << endl;
			cout << a << " < " << d << " =  " << (a < d) << endl;
			cout << a << " <= " << d << " =  " << (a <= d) << endl;
			cout << "f = f + 1 = " << (f = f + *(new LongInt("-1"))) << endl;
			cout << "e = " << e << endl;
			break;
		}
		else
			cerr << "***Error: Invalid choice***" << endl << endl;
	}

	system("pause");
	return 0;
}
