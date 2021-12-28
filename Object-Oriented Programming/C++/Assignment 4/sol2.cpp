#include <iostream>
using namespace std;

class COMPLEX {
	int r;
	int im;
public:
	COMPLEX (int i = 0, int j = 0) {
		r = i;
		im = j;
	}

	friend COMPLEX operator + (COMPLEX t1, COMPLEX t2) {
		COMPLEX C;
		C.r = t1.r + t2.r;
		C.im = t1.r + t2.im;
		return C;
	}

	friend COMPLEX operator - (COMPLEX t1, COMPLEX t2) {
		COMPLEX C;
		C.r = t1.r - t2.r;
		C.im = t1.im - t2.im;
		return C;
	}

	friend istream& operator >> (istream& is, COMPLEX &t) {
		cout << "Real: ";
		is >> t.r;
		cout << "Imaginary: ";
		is >> t.im;
		return is;
	}

	friend ostream& operator << (ostream& os, COMPLEX t) {
		os << "Real: " << t.r << " Imaginary: " << t.im << "\n";
		return os;
	}
};

int main () {
	COMPLEX c1 (7, 3), c2 (4, 1);
	COMPLEX c3;
	cin >> c3;
	cout << c3;
	c3 = c1 + c2;
	cout << c3;
	c3 = c1 - c2;
	cout << c3;
	return 0;
}