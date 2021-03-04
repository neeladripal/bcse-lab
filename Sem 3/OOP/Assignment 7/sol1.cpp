#include <iostream>
#include <string>
#include <vector>
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

};

class checkIfGivenRollIsEqual {		// function object to check if student roll is equal to given roll
	int roll;
public:
	checkIfGivenRollIsEqual (int r) : roll (r) {}

	bool operator () (const Student& s) const {
		return (roll == s.retRoll());
	}
};

class printIfScoreIsEqual {			// function object to print student details with score equal to given score
	float score;
public:
	printIfScoreIsEqual (float s) : score (s) {}

	void operator () (const Student& s) const {
		if (score == s.retScore())
			s.showData();
	}
};

class compareScore {		// compare two students on basis of score
public:
	bool operator () (const Student& s1, const Student& s2) {
		return (s1.retScore() < s2.retScore());		// increasing order
	}
};

class checkSubstring {		// check whether or not a substring is present in the name of the student
	string sub;		// substring to be matched against
	int type;		// 1 -> with substring, 0 -> without substring
public:
	checkSubstring (string n, int t) : sub(n), type(t) {}

	void operator () (const Student& s) const {
		if ((s.retName().find(sub) == string::npos) ^ type)
			s.showData();
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
			cout << "Roll number already exists.\n";
	}

	void displayStudent (int r) {

		// if there is a student in list with given roll, then display details of the student
		vector<Student>::iterator it = find_if (v.begin(), v.end(), checkIfGivenRollIsEqual(r));
		if (it == v.end())
			cout << "Roll number does not exist.\n";
		else {
			cout << "\nStudent found.\n";
			it -> showData();
		}
	}

	void modifyStudent (int r) {
		
		// if there is a student in list with given roll, then modify details of the student
		vector<Student>::iterator it = find_if (v.begin(), v.end(), checkIfGivenRollIsEqual(r));
		if (it == v.end())
			cout << "Roll number does not exist.\n";
		else {
			cout << "Enter new details-->\n";
			it -> getData (r);
			cout << "Student details modified successfully.\n";
		}
	}

	void removeStudent (int r) {

		// if there is a student in list with given roll, then remove the student
		vector<Student>::iterator it = find_if (v.begin(), v.end(), checkIfGivenRollIsEqual(r));
		if (it == v.end())
			cout << "Roll number does not exist.\n";
		else {
			v.erase(it);
			cout << "Student removed successfully.\n";
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

	void showNoOfStudents () {		// display no of students in list
		cout << "Number of students: " << v.size() << "\n";
	}

	void highestScorer () {			// display topper
		vector<Student>::iterator it = max_element (v.begin(), v.end(), compareScore());
		cout << "Student(s) with the highest score -->\n";
		for_each (v.begin(), v.end(), printIfScoreIsEqual(it -> retScore()));
	}

	void nameSubstr (int t) {		// print student details whose name either has or doesn't have a given substring
		string sub;
		cout << "Enter substring: ";
		cin >> sub;
		if (t)		// t = 1, find with substring
			cout << "Student(s) with the substring (" << sub << ") in their name(s) -->\n";
		else		// t = 0, find without substring
			cout << "Student(s) without the substring (" << sub << ") in their name(s) -->\n";
		for_each (v.begin(), v.end(), checkSubstring(sub, t));
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
			cout << "1. Add Student to List\n2. Display details of a Student\n3. Modify details of a Student\n4. Remove a Student\n";
			cout << "5. Display the list of Students\n6. Show no of students\n7. Show Highest Scorer(s)\n";
			cout << "8. Display students with a substring in their name\n9. Display students without a substring in their name\n";
			cout << "Enter your choice: ";
			cin >> ch;
			if (ch > 0 && ch < 5) {
				cout << "\nEnter roll number: ";
				cin >> r;
			}
			switch (ch) {
				case 1: S.addStudent (r); break;
				case 2: S.displayStudent (r); break;
				case 3: S.modifyStudent (r); break;
				case 4: S.removeStudent (r); break;
				case 5: S.displayList (); break;
				case 6: S.showNoOfStudents (); break;
				case 7: S.highestScorer (); break;
				case 8: S.nameSubstr (1); break;
				case 9: S.nameSubstr (0); break;
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