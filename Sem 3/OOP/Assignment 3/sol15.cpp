#include <iostream>
using namespace std;

class TRANSACTION;

class BALANCE {
	int acno;
	double balance;
	char lastUpdateDate[11];
public:
	BALANCE () {
		acno = -1;
		balance = 0;
		lastUpdateDate[0] = '\0';
	}

	void getBalanceInfo() {
		cout << "Enter the account Number: ";
		cin >> acno;
		cout << "Enter the balance: ";
		cin >> balance;
		cout << "Enter date (dd/mm/yy): ";
		cin >> lastUpdateDate;
	}

	void showBalanceInfo() {
		cout << "Account Details ---\nAccount Number: " << acno << "\n";
		cout << "Available Balance: " << balance << "\n";
		cout << "Date of Last Update: " << dateOfLastUpd << "\n";
	}

	//defining the prototype of update balance method;
	void updateBalance(TRANSACTION t);
};

class TRANSACTION {
	int tacno;
	char tdate[11];
	double tamount;
	char ttype;
public:
	void getTransactionInfo () {
		cout << "Enter transaction account number: ";
		cin >> tacno;
		cout << "Enter transaction date (dd/mm/yyyy): ";
		cin >> tdate;
		cout << "Enter transaction amount: ";
		cin >> tamount;
		cout << "Enter transaction type (W for Withdrawal, D for Deposit): ";
		cin >> ttype;
		cout << "Transaction registered successfully.\n";
	}

	void showTransactionDetails () {
		cout << "Transaction Details ---\nAccount number: " << tacno << "\n";
		cout << "Date: " << tdate << "\n";
		cout << "Amount: " << tamount << "\n";
		cout << "Type: " << ttype << "\n";
	}

	friend void BALANCE::updateBalance(TRANSACTION t);
};

void BALANCE::updateBalance(TRANSACTION t) {
	if (t.tacno == acno) {
		if (t.ttype == 'W' || t.ttype == 'w') {
			if (balance < t.tamount) {
				cout << "Sufficient Balance not available.\n ";
			}
			else {
				//withdrawal operation
				balance -= t.tamount;
				strcpy(lastUpdateDate, t.tdate);
				cout << "Transaction successful " << "\n";
				showBalanceInfo();
			}
		}
		else {
			//deposit operation
			balance += t.tamount;
			strcpy(lastUpdateDate, t.tdate);
			cout << "Transaction successful " << "\n";
			showBalanceInfo();
		}
	}
	else {
		//mismatch alert
		cout << "Account number mismatch !";
	}
}

//driver code to implment the classes
int main() {
	BALANCE b; //creating an instance of balance
	b.getBalanceInfo();
	b.showBalanceInfo();

	TRANSACTION t;
	t.getTransactionInfo();
	t.showTransactionDetails();

	//call to update balance function is made
	b.updateBalance(t);
	return 0;
}