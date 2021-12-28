#include <iostream>
#include <cstring>
using namespace std;

class String {
	char *c;
	int *pc;

public:
	String (const char *s = "") {
		int l = strlen (s);
		c = new char [l + 1];
		strcpy (c, s);
		pc = new int (1);
	}

	String (const String& S) {
		c = S.c;
		pc = S.pc;
		(*pc)++;
	}

	friend String operator + (String S1, String S2) {
		int l = strlen (S1.c) + strlen (S2.c);
		char *t = new char [l + 1];
		t[0] = '\0';
		strcat (t, S1.c);
		strcat (t, S2.c);
		String S(t);
		delete []t;
		return S;
	}

	void operator = (String S) {
		(*pc)--;
		if (*pc == 0) {
			delete []c;
			delete pc;
		}
		c = S.c;
		pc = S.pc;
		(*pc)++;
	}

	char& operator [] (int k) {
		return c[k];
	}

	friend bool operator == (String S1, String S2) {
		return (strcmp(S1.c, S2.c) == 0);
	}

	friend bool operator > (String S1, String S2) {
		return (strcmp(S1.c, S2.c) > 0);
	}

	friend bool operator < (String S1, String S2) {
		return (strcmp(S1.c, S2.c) < 0);
	}

	friend istream& operator >> (istream& is, String& S) {
		is >> S.c;
		return is;
	}

	friend ostream& operator << (ostream& os, String S) {
		os << S.c;
		return os;
	}

	~String () {
		(*pc)--;
		if (pc == 0) {
			delete []c;
			delete pc;
		}
	}

};

int main () {
	String a, b;
	cout << "Enter a: ";
	cin >> a;
	cout << "a: " << a << "\n";
	cout << "Enter b: ";
	cin >> b;
	cout << "b: " << b << "\n";
	if (a == b)
	    cout << "Both are equal.\n";
	else if (b > a)
	    cout << "b is greater.\n";
	else
	    cout << "a is greater.\n";
	b = a;
	b[0] = 'e';
	cout << "b: " << b << " a:" << a << "\n";
	cout << b[0] <<"\n";
	b = a;
	cout << a + b << "\n";
	cout << "b: " << b << "\n";
	return 0;
}