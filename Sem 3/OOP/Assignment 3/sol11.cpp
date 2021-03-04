#include <iostream>
#define MAX 5

using namespace std;

class Applicant {
	static int last_id;
	int id;
	char name[31];
	float score;
public:

	void getdata () {
		if (last_id < MAX) {
			id = last_id + 1;
			cout << "Enter name: ";
			scanf(" %[^\n]", name);
			cout << "Enter score: ";
			cin >> score;
		}
	}

	void showdata () {
		cout << "Id: " << id << " Name: " << name << " Score: " << score;
	}

	static int no_of_applicants () {
		return last_id + 1;
	}
};

int Applicant::last_id = 0;

int main () {
	Applicant a[MAX];
	char ch = 'n';
	int e;
	do {
		int op;
		printf ("1.Add applicant\n2.Show details of applicant\n3.Show no of applicants\nEnter choice: ");
		cin >> op;
		switch (op) {
			case 1:
			a[Applicant::no_of_applicants() - 1].getdata();
			break;

			case 2:
			cout << "Enter id: ";
			cin >> e;
			if (e <= Applicant::no_of_applicants()) {
				a[e - 1].showdata();
			}
			else
				cout << "Candidate does not exist.";
			break;

			case 3:
			cout << "No of applicants: " << Applicant::no_of_applicants();
			break;

			default:
			cout << "Wrong choice.";
		}
		cout << "\nDo you want to continue (y/n): ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	return 0;
}