#include <iostream>
#include <cstring>
using namespace std;

class String {
	char *c;

public:
	String (const char *s = "") {
		int l = strlen (s);
		c = new char [l + 1];
		strcpy (c, s);
	}

	String (const String& S) {
		int l = strlen (S.c);
		c = new char [l + 1];
		c[0] = '\0';
		strcpy (c, S.c);
	}

	friend String operator + (String S1, String S2) {
		int l = strlen (S1.c) + strlen (S2.c);
		char *t = new char [l + 1];
		strcat (t, S1.c);
		strcat (t, S2.c);
		String S(t);
		delete []t;
		return S;
	}

	void operator = (String S) {
		delete []c;
		int l = strlen (S.c);
		c = new char [l+1];
		c[0] = '\0';
		strcpy(c, S.c);
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
		delete []c;
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
	b = "def";
	b[0] = 'e';
	cout << "b: " << b << "\n";
	cout << b[0] <<"\n";
	b = a;
	cout << a + b << "\n";
	cout << "b: " << b << "\n";
	return 0;
}