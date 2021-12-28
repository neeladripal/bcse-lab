#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// define the class for a student
class Student {
	int roll;	// unique identifier for a student
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
	vector<Student> v;

public:

	void addStudent (int r) {

		// if there is no student in list with given roll, then add the student
		if (find_if (v.begin(), v.end(), checkIfGivenRollIsEqual(r)) == v.end()) {
			Student s;
			s.getData (r);
			v.push_back (s);
			cout << "Student added successfully.\n";
		}
		else 
			cout << "\nRoll number " << r << " already exists.\n";
	}

	void displayStudent (int r) {

		// if there is a student in list with given roll, then display details of the student
		vector<Student>::iterator it = find_if (v.begin(), v.end(), checkIfGivenRollIsEqual(r));
		if (it == v.end())
			cout << "\nRoll number " << r << " does not exist.\n";
		else {
			cout << "\nStudent found.\n";
			it -> showData();
		}
	}

	void modifyStudent (int r) {

		// if there is a student in list with given roll, then modify details of the student
		cout << "\nEnter new details-->\n";
		vector<Student>::iterator it = find_if (v.begin(), v.end(), checkIfGivenRollIsEqual(r));
		if (it == v.end())
			cout << "\nRoll number does not exist.\n";
		else {
			it -> getData (r);
			cout << "Student details modified successfully.\n";
		}
	}

	void removeStudent (int r) {

		// if there is a student in list with given roll, then remove the student
		vector<Student>::iterator it = find_if (v.begin(), v.end(), checkIfGivenRollIsEqual(r));
		if (it == v.end())
			cout << "\nRoll number does not exist.\n";
		else {
			v.erase(it);
			cout << "\nStudent removed successfully.\n";
		}
	}

	void displayList () {

		// if list is not empty, display the list of students
		if (!v.empty()) {
			cout << "\nList of Students -->\n";
			for (vector<Student>::iterator it = v.begin(); it != v.end(); it++)
				it -> showData();
		}
		else
			cout << "List is empty.\n";
	}
};

// design a class to implement mark sheet desk scenario
class MarkSheetDesk {
	queue <int> q;		// use queue to deliver result on first come first serve basis
public:
	void addRoll (int r) {		// add a roll number to the queue
		q.push (r);
		cout << "Roll no. " << r << "added to line.\n";
	}

	void showResult (StudentList &S) {	// display marksheet of the student on front of queue
		if (!q.empty()) {
			S.displayStudent (q.front());	// display marksheet upon getting the roll number
			q.pop();		// remove the roll number from the queue
		}
		else
			cout << "\nEmpty Queue.\n";
	}
};

class Batch {
public:
	static void Operations () {
		StudentList S;
		MarkSheetDesk MSD;
		char h = 'n';
		do {
			int ch, r;
			cout << "\nOperations on batch of Students -->\n";
			cout << "1. Add Student to List\n2. Display details of a Student\n3. Modify details of a Student\n4. Remove a Student\n";
			cout << "5. Display the list of Students\n6. Add Roll to Line\n7. Retrive results from Line\n";
			cout << "Enter your choice: ";
			cin >> ch;
			if (ch > 0 && ch < 5 || ch == 6) {
				cout << "\nEnter roll number: ";
				cin >> r;
			}
			switch (ch) {
				case 1: S.addStudent (r); break;
				case 2: S.displayStudent (r); break;
				case 3: S.modifyStudent (r); break;
				case 4: S.removeStudent (r); break;
				case 5: S.displayList (); break;
				case 6: MSD.addRoll (r); break;
				case 7: MSD.showResult (S); break;
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