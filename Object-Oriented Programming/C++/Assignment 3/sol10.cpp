#include <iostream>
#define MAX 1
using namespace std;

class Stack {
	int top;
	int arr[MAX];

public:

    Stack () {
		top = -1;
	}

    bool check_overflow () {
		if (top == MAX - 1) {
			cout << "\nStack overflow.";
			return false;
		}
		else
			return true;
	}
	bool check_underflow () {
		if (top == -1) {
			cout << "\nStack is empty.";
			return false;
		}
		else
			return true;
	}

	void push () {
		if (s.check_overflow()) {
			int x;
			cout << "Enter element: ";
			cin >> x;
			arr[++top] = x;
		}
	}

	void pop () {
		if (check_underflow())
			top--;
	}

	int top_element () {
			return arr[top];
	}
};

int main () {
	Stack s;
	char ch = 'n';
	int e;
	do {
		int op;
		printf ("1.Push\n2.Pop\n3.Top\nEnter choice: ");
		cin >> op;
		switch (op) {
			case 1:
			s.push();
			break;

			case 2:
			s.pop();
			break;

			case 3:
			if (s.check_underflow())
			    cout << "Top element: " << s.top_element();
			break;

			default:
			cout << "Wrong choice.";
		}
		cout << "\nDo you want to continue (y/n): ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	return 0;
}