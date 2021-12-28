#include <iostream>
#include <string>
#define MAX 5

using namespace std;

// defining the class for an individual student
class Student {
	int roll;		// roll is unique id for a student
	string name;
	float score;

public:

	void getData (int r) {		// input details of a student
		roll = r;

		cout << "Enter name: ";
		cin.ignore ();		// to ignore any newline character if present in input stream
		getline (cin, name);

		cout << "Enter score: ";
		cin >> score;
	}

	void showData () const {		// show details of a student
		cout << "Roll number: " << roll << " \tName: " << name << " \tScore: " << score << "\n";
	}
 
	int retRoll () const {		// accessor function to get roll of a student
		return roll;
	}

	int retScore () const {		// accessor function to get score of a student
		return score;
	}
};

class StudentList {
	Student list[MAX];		// defining an array of students
	int count;		// size of the list of students

	int searchStudent (int r) {		// search for existence of a student, given roll no
		for (int i = 0; i < count; i++)
			if (list[i].retRoll() == r)
				return i;		// if found, returns the index
		return -1;		// else returns -1
	}

	float highestMarks () {
		float m = 0;
		for (int i = 0; i < count; i++)
			if (list[i].retScore() > m)
				m = list[i].retScore();
		return m;
	}

public:

	StudentList () {
		count = 0;		// size of list must be 0 at the beginning
	}

	void addStudent () {
		if (count == MAX)	// if list goes out of bounds, throw exception
			throw "\nList out of bounds.";

		// take input of the unique id, i.e., roll
		int r;
		cout << "\nEnter roll number: ";
		cin >> r;

		// if student is not present, add to list
		if (searchStudent (r) == -1) {
			list[count++].getData (r);
			cout << "Student added successfully.\n";
		}
		else 
			cout << "Roll number already exists.\n";
	}

	void displayStudent () {

		// take input of the unique id, i.e., roll
		int r;
		cout << "\nEnter roll number: ";
		cin >> r;

		int i = searchStudent (r);		// search for the required student in the list

		// if student found, display the details
		if (i == -1)
			throw "Roll number does not exist.\n";
		else {
			cout << "Student found.\n";
			list[i].showData();
		}
	}

	void displayToppers () {
		if (count) {
			float maxMarks = highestMarks;
			cout << "\nList of toppers -->\n";
			for (int i = 0; i < count; i++)
				if (list[i].retScore() == maxMarks)
					list[i].showData();
		}
		else
			throw "List is empty.\n";
	}

	void averageScore () {
		if (count) {
			float sumMarks = 0;
			for (int i = 0; i < count; i++)
				sumMarks += list[i].retScore();
			cout << "\nAverage Score = " << sumMarks/count;
		}
		else
			throw "List is empty.\n";
	}

	void displayList () {

		// if list is not empty, display details of all students
		if (count) {
			cout << "\nList of Students -->\n";
			for (int i = 0; i < count; i++)
				list[i].showData();
		}
		else
			throw "List is empty.\n";
	}
};

class Batch {
public:
	static void Operations () {
		StudentList L;
		char h = 'n';

		do {
			int ch, r;
			cout << "\n1. Add Student 2. Display details of a Student 3. Display list of students\nEnter your choice: ";
			cin >> ch;

			switch (ch) {
				case 1:
					try {
						L.addStudent();
					}
					catch (char const* c) {		// catch the exception, in case list goes out of bounds
						cout << c << "\n";
					}
					break;
				case 2:
					L.displayStudent();
					break;
				case 3:
					L.displayList();
					break;
				default:
					cout << "Wrong choice.\n";
			}

			cout << "\nDo you want to continue (y/n) ? ";
			cin >> h;
		} while (h == 'Y' || h == 'y');
	}
};

int main () {
	Batch::Operations();
	return 0;
}