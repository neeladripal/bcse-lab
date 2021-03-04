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

	bool operator == (const Student& s) const {		// two students are equal if their roll are equal
		return (roll == s.roll);
	}

	bool operator < (const Student& s) const {		// two students are compared on the basis of their score
		return (roll < s.roll);		// increasing order
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

class compareScoreDesc {	// compare two students on basis of score
public:
	bool operator () (const Student& s1, const Student& s2) {
		return (s1.retScore() > s2.retScore());		// decreasing order
	}
};

class compareScoreAsc {		// compare two students on basis of score
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

	void operator () (const Student& s) {
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
			cout << "Student found.\n";
			it -> showData();
		}
	}

	void modifyStudent (int r) {

		// if there is a student in list with given roll, then modify details of the student
		cout << "\nEnter new details-->\n";
		vector<Student>::iterator it = find_if (v.begin(), v.end(), checkIfGivenRollIsEqual(r));
		if (it == v.end())
			cout << "Roll number does not exist.\n";
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

	void showNoOfStudents () {		// display no of students in list
		cout << "\nNumber of students: " << v.size() << "\n";
	}

	void highestScorer () {			// display topper
		vector<Student>::iterator it = max_element (v.begin(), v.end(), compareScoreAsc());
		cout << "\nStudent(s) with the highest score -->\n";
		for_each (v.begin(), v.end(), printIfScoreIsEqual(it -> retScore()));
	}

	void nameSubstr (int t) {		// print student details whose name either has or doesn't have a given substring
		string sub;
		cout << "\nEnter substring: ";
		cin >> sub;
		if (t)		// t = 1, find with substring
			cout << "Students with the substring (" << sub << ") in their names -->\n";
		else		// t = 0, find without substring
			cout << "Students without the substring (" << sub << ") in their names -->\n";
		for_each (v.begin(), v.end(), checkSubstring(sub, t));
	}

	void sortByScoreDesc () {		// sort student list in descending order of scores
		sort (v.begin(), v.end(), compareScoreDesc());
		cout << "\nList sorted in descending order of score.\n";
		displayList ();
	}

	void combine (const StudentList& L) {
		StudentList M;		// declare a new list
		M.v = v;		// copy contents of first list into new list
		copy (L.v.begin(), L.v.end(), back_inserter(M.v));		// copy contents of second list into new list
		sort (M.v.begin(), M.v.end());		// sort the new list
		M.v.erase (unique(M.v.begin(), M.v.end()), M.v.end());		// delete students with same roll
		cout << "\nCombined Collection -->";
		M.displayList ();	// print the combined list
	}
};

class Batch {
public:
	static void Operations () {
		vector <StudentList> Sv;	// use vector of student list to represent collection
		
		StudentList L;
		Sv.push_back(L);
		
		char h = 'n';
		int cur = 0;
		do {
			int ch, r;
			cout << "\nOperations on Collection " << cur + 1 << " of Students -->\n";
			cout << "1. Add Student to List\n2. Display details of a Student\n3. Modify details of a Student\n4. Remove a Student\n";
			cout << "5. Display the list of Students\n6. Show no of students\n7. Show Highest Scorer(s)\n";
			cout << "8. Display students with a substring in their name\n9. Display students without a substring in their name\n";
			cout << "10. Sort the list in descending order of scores\n";
			cout << "11. Add another collection\n12. Switch to another collection\n13. Merge two collections\n";
			cout << "Enter your choice: ";
			cin >> ch;
			
			if (ch > 0 && ch < 5) {
				cout << "\nEnter roll number: ";
				cin >> r;
			}
			int cn1 = 0, cn2 = 0;

			switch (ch) {
				case 1: Sv[cur].addStudent (r); break;
				case 2: Sv[cur].displayStudent (r); break;
				case 3: Sv[cur].modifyStudent (r); break;
				case 4: Sv[cur].removeStudent (r); break;
				case 5: Sv[cur].displayList (); break;
				case 6: Sv[cur].showNoOfStudents (); break;
				case 7: Sv[cur].highestScorer (); break;
				case 8: Sv[cur].nameSubstr (1); break;
				case 9: Sv[cur].nameSubstr (0); break;
				case 10: Sv[cur].sortByScoreDesc (); break;
				case 11: 
					Sv.push_back(L);		// add a new collection
					cout << "\nNew Collection added. Total collection count: " << Sv.size() << "\n"; 
					break;

				case 12: 
					cout << "\nChoose collection (1 - " << Sv.size() << "): ";
					cin >> cn1;		// choose the collection number
					
					if (cn1 > 0 && cn1 <= Sv.size()) {
						cur = cn1 - 1;		// switch to it, if available
						cout << "Switched to collection " << cn1 << "\n";
					}
					else
						cout << "Collection not available.\n";
					
					break;

				case 13:
					cout << "\nChoose first collection (1 - " << Sv.size() << "): ";
					cin >> cn1;
					
					cout << "Choose second collection (1 - " << Sv.size() << "): ";
					cin >> cn2;
					
					if (cn1 > 0 && cn1 <= Sv.size() && cn2 > 0 && cn2 <= Sv.size())
						Sv[cn1 - 1].combine(Sv[cn2 - 1]);		// combine both collections
					else if (cn1 <= 0 && cn1 > Sv.size())
						cout << "First Collection not available.\n";
					else if (cn2 <= 0 && cn2 > Sv.size())
						cout << "Second Collection not available.\n";
					
					break;

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