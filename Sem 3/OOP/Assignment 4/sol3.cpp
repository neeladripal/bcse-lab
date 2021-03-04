#include <iostream>
using namespace std;

class Array {
	int *p;
	int size;

public:
	Array (int s = 0) {
		size = s;
		if (size == 0)
			p = NULL;
		else
			p = new int [size];
	}

	Array (const Array& A) {
		size = A.size;
		if (size == 0)
			p = NULL;
		else {
			p = new int [size];
			for (int i = 0; i < size; i++)
				p[i] = A.p[i];
		}
	}

	friend Array operator + (Array A, Array B) {
		int i = 0;
		if (A.size > B.size) {
			Array C(A.size);
			while (i < B.size){
				C.p[i] = A.p[i] + B.p[i];
				i++;
			}
			while (i < A.size) {
				C.p[i] = A.p[i];
				i++;
			}
			return C;
		}
		else {
			Array C(B.size);
			while (i < A.size){
				C.p[i] = A.p[i] + B.p[i];
				i++;
			}
			while (i < B.size) {
				C.p[i] = B.p[i];
				i++;
			}
			return C;
		}
	}

	void operator = (Array A) {
		delete []p;
		size = A.size;
		if (size == 0)
			p = NULL;
		else {
			p = new int [size];
			for (int i = 0; i < size; i++)
				p[i] = A.p[i];
		}
	}

	int& operator [] (int k) {
		return p[k];
	}

	Array operator * (int k) {
		Array C(size);
		for (int i = 0; i < size; i++)
			C.p[i] = k * p[i];
		return C;
	}

	friend Array operator * (int k, Array A) {
		Array C(A.size);
		for (int i = 0; i < A.size; i++)
			C.p[i] = k * A.p[i];
		return C;
	}

	friend istream& operator >> (istream& is, Array& A) {
		cout << "Enter array elements: ";
		for (int i = 0; i < A.size; i++)
			is >> A.p[i];
		return is;
	}

	friend ostream& operator << (ostream& os, Array A) {
		cout << "Array: ";
		for (int i = 0; i < A.size; i++)
			os << A.p[i] << " ";
		os << "\n";
		return os;
	}

	~Array () {
		if (p != NULL)
			delete []p;
	}

};

int main () {
	int s;
	cout << "Enter size: ";
	cin >> s;
	Array a(s);
	cin >> a;
	Array b(a);
	Array c = a + b;
	cout << c;
	c = a;
	cout << "\nArray C: ";
	for (int i = 0; i < s; i++)
		cout << c[i] << " ";
	c = a * 5;
	cout << "\nArray C: ";
	for (int i = 0; i < s; i++)
		cout << c[i] << " ";
	c = 5 * a;
	cout << "\nArray C: ";
	for (int i = 0; i < s; i++)
		cout << c[i] << " ";
	return 0;
}