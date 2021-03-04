#include <iostream>

using namespace std;

class Student {
	static int last_roll;
	int roll;
	char name[31];
	char course[31];
	char admission_date[11];
	float marks[5];
	bool marks_assigned;

public:

	void get_admission () {
		cout << "Enter roll: ";
		cin >> roll;
		cout << "Enter name: ";
		scanf (" %[^\n]", name);
		cout << "Enter course: ";
		scanf (" %[^\n]", course);
		cout << "Enter admission_date (dd/mm/yyyy): ";
		scanf (" %[^\n]", admission_date);
	}

	void assign_marks () {
		cout << "Enter marks in five subjects: ";
		for (int i = 0; i < 5; i++)
			cin >> marks[i];
		marks_assigned = true;
	}

	void marksheet () {
		if (marks_assigned == true) {
			cout << "Roll: " << roll << ", Name: " << name << ", Course: " << course << "\n";
			cout << "Marks: ";
			for (int i = 0; i < 5; i++)
				cout << marks[i] << " ";
			printf("\n");
		}

		else
			cout << "Marks not assigned.\n";
	}
};

int main() {
	Student s1;
	s1.get_admission();

	s1.marksheet();
	s1.assign_marks();

	s1.marksheet();
	return 0;
}