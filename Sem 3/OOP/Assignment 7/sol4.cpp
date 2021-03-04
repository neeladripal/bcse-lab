#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

// define the class for a student
class Student {
	int roll;
	string name;
	float score;
public:

	// input details of a student
	void getData (int r) {
		roll = r;
		cout << "Enter name: ";
		cin.ignore ();
		getline (cin, name);
		cout << "Enter score: ";
		cin >> score;
	}

	// print details of a student
	void showData () const {
		cout << "Roll number: " << roll << " \tName: " << name << " \tScore: " << score << "\n";
	}
 
	int retRoll () const {			// accessor function to get roll
		return roll;
	}

	string retName () const {		// accessor function to get name
		return name;
	}

	float retScore () const {		// accessor function to get score
		return score;
	}

	bool operator == (const Student& s) const {		// two students are equal if their roll are equal
		return (roll == s.roll);
	}

	bool operator < (const Student& s) const {		// two students are compared on the basis of their score
		return (score > s.score);		// decreasing order
	}
};

class checkIfGivenRollIsEqual {		// function object to check if student roll is equal to given roll
	int roll;
public:

	checkIfGivenRollIsEqual (int r) : roll (r) {}

	bool operator () (const Student& s) const {
		return (roll == s.retRoll());
	}
};

// design a class to handle operations on a list of students
class StudentList {
	set<Student> st;	// use a set because roll must be unique and list must be sorted according to score

public:

	void addStudent (int r) {

		// if there is no student in list with given roll, then add the student
		if (find_if (st.begin(), st.end(), checkIfGivenRollIsEqual(r)) == st.end()) {
			Student s;
			s.getData (r);
			st.insert (s);
			cout << "Student added successfully.\n";
		}
		else 
			cout << "Roll number already exists.\n";
	}

	void displayStudent (int r) {

		// if there is a student in list with given roll, then display details of the student
		set<Student>::iterator it = find_if (st.begin(), st.end(), checkIfGivenRollIsEqual(r));

		if (it == st.end())
			cout << "Roll number does not exist.\n";
		else
			it -> showData();
	}

	void removeStudent (int r) {
		
		// if there is a student in list with given roll, then remove the student
		set<Student>::iterator it = find_if (st.begin(), st.end(), checkIfGivenRollIsEqual(r));

		if (it == st.end())
			cout << "Roll number does not exist.\n";
		else {
			st.erase(it);
			cout << "Student removed successfully.\n";
		}
	}

	void displayList () {
		
		// if list is not empty, display the list of students
		if (!st.empty()) {
			cout << "\nList of Students -->\n";
			for (set<Student>::iterator it = st.begin(); it != st.end(); it++)
				it -> showData();
		}
		else
			cout << "List is empty.\n";
	}
};

class Batch {
public:
	static void Operations () {
		StudentList S;
		char h = 'n';
		do {
			int ch, r;
			cout << "\nOperations on batch of Students -->\n";
			cout << "1. Add Student to List\n2. Display details of a Student\n";
			cout << "3. Remove a Student\n4. Display the list of Students\n";
			cout << "Enter your choice: ";
			cin >> ch;
			if (ch > 0 && ch < 4) {
				cout << "\nEnter roll number: ";
				cin >> r;
			}
			switch (ch) {
				case 1: S.addStudent (r); break;
				case 2: S.displayStudent (r); break;
				case 3: S.removeStudent (r); break;
				case 4: S.displayList (); break;
				default: cout << "Wrong choice.\n";
			}
			cout << "\nDo you want to continue (y/n) ? ";
			cin >> h;
		} while (h == 'y' || h == 'Y');
	}
};

int main () {
	Batch::Operations();
	return 0;
}