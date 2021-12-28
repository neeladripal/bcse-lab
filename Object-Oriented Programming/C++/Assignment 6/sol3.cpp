#include <iostream>
#include <string>
using namespace std;

template <class T>

class Array {
	T *p;	// pointer to object of type T
	int size;	// size of array

public:
	Array (int s = 0) {		// default constructor accepting size as argument
		size = s;

		if (size == 0)
			p = NULL;		// if size is 0, set pointer to NULL
		else
			p = new T [size];		// else, set pointer to dynamically allocated array
	}

	Array (const Array& A) {	// copy constructor
		size = A.size;			// copy size
		
		if (size == 0)
			p = NULL;		// if size is 0, set pointer to NULL
		else {
			p = new T [size];		// else, set pointer to dynamically allocated array
			for (int i = 0; i < size; i++)
				p[i] = A.p[i];		// copy into new array
		}
	}

	friend Array<T> operator + (Array<T> A, Array<T> B) {		// concatenates two arrays
		int i = 0;
		
		Array<T> C(A.size + B.size);		// create a new array C of size = size of A + size of B
		while (i < A.size){
				C.p[i] = A.p[i];			// copy contents of A into C
				i++;
			}
			while (i < B.size) {
				C.p[i] = B.p[i];			// copy contents of B into C
				i++;
			}
		return C;
	}

	void operator = (Array<T> A) {			// assign an array to another array
		delete []p;							// delete previous contents of array

		// copy contents of array
		size = A.size;
		if (size == 0)
			p = NULL;
		else {
			p = new T [size];
			for (int i = 0; i < size; i++)
				p[i] = A.p[i];
		}
	}

	T& operator [] (int k) {		// returns element at ith index
		if (size == 0)
			throw "Array is empty.";		// if size is 0, throw exception
		if (k < 0 || k >= size)
			throw "Index out of bounds.";	// if index is out of bounds, throw exception
			
		return p[k];
	}

	friend istream& operator >> (istream& is, Array<T>& A) {		// to take input for array
		for (int i = 0; i < A.size; i++)
			is >> A.p[i];
		return is;
	}

	friend ostream& operator << (ostream& os, Array<T> A) {			// to print the array
		for (int i = 0; i < A.size; i++)
			os << A.p[i] << " ";
		return os;
	}

	T sum () {		// returns sum of elements in array
		if (size == 0)
			throw "Array is empty.";	// is size is 0, throw exception
		
		// calculate sum
		T s = p[0];
		for (int i = 1; i < size; i++)
			s += p[i];
		return s;
	}

	T max_element () {		// returns maximum elements in array
		if (size == 0)
			throw "Array is empty.";	// is size is 0, throw exception
		
		// calcualte maximum element
		T m = p[0];
		for (int i = 1; i < size; i++)
			if (p[i] > m)
				m = p[i];
		return m;
	}

	~Array () {
		if (p != NULL)
			delete []p;		// if array is non-empty, release the dynamically allocated space
	}

};

int main () {
	char h = 'n';
	do {
		int t;
		cout << "\nWhat type of array is needed?\n1. int 2. float 3. double\nEnter your choice: ";
		cin >> t;

		if (t == 1) {
			// input size
			int s;
			cout << "Enter size: ";
			cin >> s;

			// input array
			Array <int> A(s);
			cout << "Enter Array: ";
			cin >> A;

			// display array
			cout << "\nArray: " << A << "\n";

			// display sum
			try {
				cout << "Sum of elements of b: " << A.sum() << "\n";
			}
			catch (char const* c) {
				cout << c << "\n";
			}

			// display maximum element
			try {
				cout << "Max element: " << A.max_element() << "\n";
			}
			catch (char const* c) {
				cout << c << "\n";
			}
		}

		else if (t == 2) {
			// input size
			int s;
			cout << "Enter size: ";
			cin >> s;

			// input array
			Array <float> A(s);
			cout << "Enter Array: ";
			cin >> A;

			// display array
			cout << "\nArray: " << A << "\n";

			// display sum
			try {
				cout << "Sum of elements of b: " << A.sum() << "\n";
			}
			catch (char const* c) {
				cout << c << "\n";
			}

			// display maximum element
			try {
				cout << "Max element: " << A.max_element() << "\n";
			}
			catch (char const* c) {
				cout << c << "\n";
			}
		}

		else if (t == 3) {
			// input size
			int s;
			cout << "Enter size: ";
			cin >> s;

			// input array
			Array <double> A(s);
			cout << "Enter Array: ";
			cin >> A;

			// display array
			cout << "\nArray: " << A << "\n";

			// display sum
			try {
				cout << "Sum of elements of b: " << A.sum() << "\n";
			}
			catch (char const* c) {
				cout << c << "\n";
			}

			// display maximum element
			try {
				cout << "Max element: " << A.max_element() << "\n";
			}
			catch (char const* c) {
				cout << c << "\n";
			}
		}
		
		else
			cout << "Wrong choice.\n";

		cout << "\nDo you want to continue (y/n) ? ";
		cin >> h;

	} while (h == 'y' || h == 'Y');

	return 0;
}