#include <iostream>
using namespace std;

class Employee {
	int empid;
	char name[31];
	char designation[31];
protected:
	float basicpay;
	float salary;
public:
	void getData (int id) {
		empid = id;
		cout << "Enter name: ";
		scanf (" %[^\n]", name);
		cout << "Enter designation: ";
		scanf (" %[^\n]", designation);
		cout << "Enter basic pay: ";
		cin >> basicpay;
	}
	void showData () {
		cout << "Employee Details -->\n";
		cout << "Employee id: " << empid << "\n";
		cout << "Name: " << name << "\n";
		cout << "Designation: " << designation << "\n";
		cout << "Basic Pay: " << basicpay << "\n";
		cout << "Salary: " << salary << "\n";
	}

	virtual void computeSalary () {};
};

class Permanent: public Employee {
public:
	void computeSalary () {
		salary = 2.1 * basicpay;
	}
};

class Contractual: public Employee {
	float allowance;
public:
	void getAllowance () {
		cout << "Enter allowance: ";
		cin >> allowance;
	}

	void computeSalary () {
		getAllowance();
		salary = basicpay + allowance;
	}
};

int main () {
	Employee *p;
	int ch, id;
	cout << "1.Permanent 2.Contractual\nEnter employee type: ";
	cin >> ch;
	if (ch == 1) {
		Permanent P;
		p = &P;
	}
	else if (ch == 2) {
		Contractual C;
		p = &C;
	}
	else {
		cout << "Wrong choice.\n";
		return 0;
	}
	cout << "Enter employee id: ";
	cin >> id;
	p -> getData(id);
	p -> computeSalary();
	p -> showData();
	return 0;
}
