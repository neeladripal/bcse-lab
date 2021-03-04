#include <iostream>

#define MAX_ENTRIES 1000
#define MAX_STUDENT 100
#define MAX_SUBJECT 10

using namespace std;

class StudentSubject {	// design time class
	int sroll;			// unique roll of student
	int subcode;		// unique code of subject
	friend class StudentSubjectList;
public:
	StudentSubject () {		// defalult constructor to initialise a student-subject pair
		sroll = -1;
		subcode = -1;
	}
};

class StudentSubjectList {			// array of unique identifier pair
	static StudentSubject list[MAX_ENTRIES];		// list of all student-subject pairs
	static int count;								// no of student-subject pairs
public:

	static void addEntry (int r, int c) {			// function to add an entry into the list
		list[count].sroll = r;
		list[count].subcode = c;
		count++;
	}

	static int searchStudentRoll (int c, int* r) {	// function to search all entries when subject code is given
		int n = 0;
		for (int i = 0; i < count; i++)
			if (list[i].subcode == c) {
				r[n++] = list[i].sroll;
			}
		return n;
	}

	static int searchSubjectCode (int r, int* c) {	// function to search all subjects when student roll is given
		int n;
		for (int i = 0; i < count; i++)
			if (list[i].sroll == r) {
				c[n++] = list[i].subcode;
			}
		return n;
	}
};

class Subject {
	int code;			// unique code of a subject
	char name[31];		// name of a subject
	friend class SubjectList;
public:
	Subject () {
		code = -1;
		name[0] = '\0';
	}

	void getData (int c) {	// function to get data for a subject
		code = c;
		cout << "\nEnter subject name: ";
		scanf (" %[^\n]", name);
	}

	void showData () {			//	function to show subject details
		cout << "\nSubject Code: " << code << ", Name: " << name;
	}
};

class SubjectList {				// list of subjects
	static Subject list[MAX_SUBJECT];
	static int count;
public:

	static int search (int subcode) {		// search for a subject in the list
		for (int i = 0; i < count; i++)
			if (list[i].code == subcode)
				return i;
		return -1;
	}

	static void addSubject () {				// add a subjecta to the list
		int c;
		cout << "\nEnter subject code: ";
		cin >> c;
		if (search(c) >= 0)
			cout << "\nSubject already exists.";
		else {
			list[count++].getData(c);
			cout << "\nSubject added successfully.";
		}
	}

	static void displaySubjectbyStudentRoll ();	// given a student roll, display subjects taken by him
};

class Student {
	int roll;
	char name[31];
	friend class StudentList;
public:
	Student () {
		roll = -1;
		name[0] = '\0';
	}

	bool getData (int r) {						// get data for a student
		roll = r;
		cout << "\nEnter student name: ";
		scanf (" %[^\n]", name);
		int subcount = 0;
		cout << "\nEnter no of subjects: ";
		cin >> subcount;
		if (subcount > 0) {
			cout << "\nEnter the subject codes -->";
			for (int i = 0; i < subcount; i++) {
				int c;
				cout << "\nSubject " << i + 1 << " :";
				cin >> c;
				if (SubjectList::search(c) >= 0) 		// search if the subject exists
					StudentSubjectList::addEntry (r, c);		// add an entry to the student-subject pair list
				else
					cout << " This subject does not exist.";
			}
			return true;
		}
		else {
			cout << "\nNo of subjects must be greater than zero.";
			return false;
		}
	}

	void showData() {						// show details of a subject
		cout << "\nStudent Roll: " << roll << ", Name: " << name;
	}
};

class StudentList {								// list of students
	static Student list[MAX_STUDENT];
	static int count;
public:

	static int search (int sroll) {				// search for a student in the list
		for (int i = 0; i < count; i++)
			if (list[i].roll == sroll)
				return i;
		return -1;
	}

	static void addStudent () {					// add a student to the list
		int r;
		cout << "\nEnter student roll: ";
		cin >> r;
		if (search(r) >= 0)
			cout << "\nStudent already exists.";
		else
			if(list[count++].getData(r))
				cout << "\nStudent added successfully.";
			else {
				cout << "\nStudent could not be added.";
				count--;
			}
	}

	static void displayStudentbySubjectCode () {		// given a subject code, show the students studying the subject
		int c;
		cout << "\nEnter subject code: ";
		cin >> c;
		if (SubjectList::search(c) >= 0) {		// search if the subject exists
			int r[MAX_STUDENT];
			int n = StudentSubjectList::searchStudentRoll (c, r);		// search the student-subject pair list for entries with given subject code
			cout << n << "students found.";
			for (int i = 0; i < n; i++)
				list[search(r[i])].showData();		// show details of the corresponding students
		}
		else
			cout << "\nStudent does not exist.";
	}
};

void SubjectList::displaySubjectbyStudentRoll () {   // given a student roll, display subjects taken by him	
		int r;
		cout << "\nEnter student roll: ";
		cin >> r;
		if (StudentList::search(r) >= 0) {			// search for the student in student list
			int c[MAX_SUBJECT];
			int n = StudentSubjectList::searchSubjectCode (r, c);	// search in student-subject pair list for entries with the given student roll
			cout << n << "subjects found.";
			for (int i = 0; i < n; i++)
				list[search(c[i])].showData();		// show details of the corresponding subjects
		}
		else
			cout << "\nStudent does not exist.";
	}











StudentSubject StudentSubjectList::list[MAX_ENTRIES];
int StudentSubjectList::count;
Subject SubjectList::list[MAX_SUBJECT];
int SubjectList::count;
Student StudentList::list[MAX_STUDENT];
int StudentList::count;

class Menu {
public:
	static void operations () {
		char h = 'n';
		do {
			int ch, op, r, c;
			cout << "\n1.Add Subject 2. Add Student 3. Display Subjects by Student Roll 4. Display Students by Subject Code\nEnter your choice: ";
			cin >> ch;
			switch(ch) {
				case 1: SubjectList::addSubject(); break;
				case 2: StudentList::addStudent(); break;
				case 3: SubjectList::displaySubjectbyStudentRoll(); break;
				case 4: StudentList::displayStudentbySubjectCode(); break;
			}
			cout << "\nDo you want to continue (y/n) ? ";
			cin >> h;
		} while (h == 'y' || h == 'Y');
	}
};

int main () {
	Menu::operations();
	return 0;
}