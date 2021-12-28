#include <iostream>
using namespace std;

class Account {
	int acno;
	double balance;
	Account *next;
public:
	// Constructor to initialise new account
	Account () {
		acno = -1;
		balance = 0;
		next = NULL;
	}

	// Function to get data for new account
	bool getdata () {
		cout << "Enter account number: ";
		cin >> acno;
		cout << "Enter balance (>=0): ";
		cin >> balance;
		if (balance < 0)
			return false;
		else
			return true;
	}

	// Function to show the details of an existing account
	void showdata () {
		cout << "Account Number: " << acno << ", Balance: " << balance << "\n";
	}

	// AccountList needs access to acno and balance private data members
	friend class AccountList;
};

class Withdraw {
	int wacno;
	double wamount;
public:
	// Constructor to create new withdraw request
	Withdraw () {
		wacno = -1;
		wamount = 0;
	}

	// Function to accept details of withdraw request
	void getdata () {
		cout << "Enter account number: ";
		cin >> wacno;
		cout << "Enter the amount to withdraw: ";
		cin >> wamount;
	}

	// AccountList needs access to wacno and wamount private data members
	friend class AccountList;
};

class AccountList {
	Account *head;

	// Function to search for an account, given the account number
	Account* search (int no) {
		for (Account *cur = head; cur != NULL; cur = cur -> next)
			if (cur -> acno == no) {
				cout << "Account Number: " << no << " exists. ";
				return cur;
			}
		cout << "Account does not exist.\n";
		return NULL;
	}

public:
	// Constructor to initialise an empty list
	AccountList () {
		head = NULL;
	}

	// Function to add a new account
	void add () {
		Account *newNode = new Account;
		bool ok = newNode -> getdata();
		if (search(newNode -> acno)) {
			cout << "Enter unique account number.\n";
			delete newNode;
		}
		else if (ok) {
			newNode -> next = head;
			head = newNode;
			cout << "Account added successfully.\n";
		}
		else {
			cout << "Balance must be greater than zero.\n";
			delete newNode;
		}
	}

	// Function to display the details of all existing accounts
	void display () {
		if (head == NULL)
			cout << "No accounts to display.\n";
		else
			for (Account *cur = head; cur != NULL; cur = cur -> next)
				cur -> showdata ();
	}

	// Function to create and process a withdraw request
	void withdraw () {
		Withdraw W;
		W.getdata();
		Account *t = search (W.wacno);
		if (t) {
			if (t -> balance < W.wamount)
				cout << "Not enough cash to withdraw.\n";
			else {
				t -> balance -= W.wamount;
				cout << "Transaction successful.\n";
			}
		}
	}

	// Function to delete the entire account list
	void del () {
		Account *auxiliaryNode = head;
		while (auxiliaryNode != NULL) {
			auxiliaryNode = auxiliaryNode -> next;
			delete auxiliaryNode;
		}
	}
};

class Operations {
public:

	// Driver Code
	static void listOperations () {
		AccountList L;
		char ch = 'n';
		do {
			int op;
			cout << "1. Add account\n2. Display all accounts\n3. Withdraw amount from an account\nEnter your option: ";
			cin >> op;
			switch (op) {
				case 1: L.add(); break;
				case 2: L.display(); break;
				case 3: L.withdraw(); break;
				default: cout << "Option not available.\n";
			}
			cout << "Do you want to continue? (y/n)\n";
			cin >> ch;
		} while (ch == 'y'|| ch == 'Y');
		L.del();
	}
};

int main () {
	Operations::listOperations();
	return 0;
}