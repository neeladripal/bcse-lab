#include <iostream>
#define MAX 10
using namespace std;

class Item {
	int code;
	char name[31];
	float rate;
	int quantity;
public:
	// function to return the item code
	int getItemCode () const{
		return code;
	}
	// function to receive the data for an item
	void getData (int x) {
		code = x;
		cout << "Enter name of item: ";
		scanf(" %[^\n]", name);
		cout << "Enter rate of item: ";
		cin >> rate;
		cout << "Enter quantity of item: ";
		cin >> quantity;
		cout << "Item added successfully.\n";
	}

	// function to show the data of an item
	void showData () {
		cout << "Item Code: " << code << ", Name: " << name << ", Rate: " << rate << ", Quantity available: " << quantity <<"\n";
	}

	// function to update the rate of an item
	void updateRate () {
		cout << "Enter new rate: ";
		cin >> rate;
		cout << "Rate updated successfully.\n";
	}

	// function to decrease the quantity available by the quantity issued
	void issue () {
		int x;
		cout << "Enter issued quantity: ";
		cin >> x;
		if (quantity >= x) {
			quantity -= x;
			cout << "Quantity issued.\n";
		}
		else
			cout << "Issue quantity is more than available quantity.\n";
	}

	// function to increase the quantity available by the quantity received
	void receive () {
		int x;
		cout << "Enter received quantity: ";
		cin >> x;
		quantity += x;
		cout << "Quantity received.\n";
	}
};

class List {
	Item A[MAX]; // declare an array of item variables
	int count; // keeps count of the no of items in the list

	// function returns true if item is present
	int checkItem (int t) {
		cout << "Enter item code: ";
		cin >> t;
		for (int i =0; i < count; i++)
			if (A[i].getItemCode() == t)
				return i;
		return -1;
	}

public:
	List() {
		count = 0;
	}

	void listOperations () {
		char h = 'n';
		do {
			int icode;
			cout << "Enter item code: ";
			cin >> icode;
			int i = checkItem(icode);
			if (i == -1) {
				char ch = 'n';
				cout << "Item does not exist. Do you want to add it? Press y to confirm.";
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
					A[count++].getData(icode);
				else
					cout << "You chose not to add the item.\n";
			}
			else {
				int op;
				cout << "Item exists.\n1.Show Details\n2.Update Rate\n3.Update quantity\n4.Delete item\nEnter your option: ";
				cin >> op;
				char ch;
				switch (op) {
					case 1: A[i].showData(); break;
					case 2: A[i].updateRate(); break;
					case 3: 
						cout << "a.Issue  b.Receive\nEnter choice: ";
						cin >> ch;
						if (ch == 'a'|| ch == 'A')
							A[i].issue();
						else if (ch == 'b' || ch == 'B')
							A[i].receive();
						else
							cout << "Wrong choice.\n";
						break;
					case 4: 
						for (int j = i; j < count - 1; j++)
							A[j] = A[j+1];
						count--;
						break;
					default: cout << "Option not available.\n";
				}
			}
			cout << "Do you want to continue? (y/n)\n";
			cin >> h;
		} while (h == 'y'|| h == 'Y');
	}
};

int main () {
	List L;
	L.listOperations();
	return 0;
}