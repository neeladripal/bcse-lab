#include <iostream>

#define MAX_ENTRIES 1000
#define MAX_STUDENT 100
#define MAX_SUBJECT 10

using namespace std;

class StudentList;

class StudentSubject {
	int sroll;			// unique roll of student
	int subcode;		// unique code of subject
	friend class StudentSubjectList;
public:
	StudentSubject () {		// defalult constructor to initialise a student-subject pair
		sroll = -1;
		subcode = -1;
	}
};

class StudentSubjectList {
	StudentSubject list[MAX_ENTRIES];		// list of all student-subject pairs
	int count;								// no of student-subject pairs
public:

	void addEntry (int r, int c) {			// function to add an entry into the list
		list[count].sroll = r;
		list[count].subcode = c;
		count++;
	}

	int searchStudentRoll (int c, int* r) {	// function to search all entries when subject code is given
		int n = 0;
		for (int i = 0; i < count; i++)
			if (list[i].subcode == c) {
				r[n++] = list[i].sroll;
			}
		return n;
	}

	int searchSubjectCode (int r, int* c) {	// function to search all subjects when student roll is given
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

	void getData (int c) {
		code = c;
		cout << "\nEnter subject name: ";
		scanf (" %[^\n]", name);
	}

	void showData () {
		cout << "\nSubject Code: " << code << ", Name: " << name;
	}
};

class SubjectList {
	Subject list[MAX_SUBJECT];
	int count;
public:

	int search (int subcode) {
		for (int i = 0; i < count; i++)
			if (list[i].code == subcode)
				return i;
		return -1;
	}

	void addSubject () {
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

	void displaySubjectbyStudentRoll (StudentList&, StudentSubjectList&);
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

	bool getData (int r, SubjectList& Y, StudentSubjectList& Z) {
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
				if (Y.search(c) >= 0) 
					Z.addEntry (r, c);
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

	void showData() {
		cout << "\nStudent Roll: " << roll << ", Name: " << name;
	}
};

class StudentList {
	Student list[MAX_STUDENT];
	int count;
public:

	int search (int sroll) {
		for (int i = 0; i < count; i++)
			if (list[i].roll == sroll)
				return i;
		return -1;
	}

	void addStudent (SubjectList& Y, StudentSubjectList& Z) {
		int r;
		cout << "\nEnter student roll: ";
		cin >> r;
		if (search(r) >= 0)
			cout << "\nStudent already exists.";
		else
			if(list[count++].getData(r, Y, Z))
				cout << "\nStudent added successfully.";
			else {
				cout << "\nStudent could not be added.";
				count--;
			}
	}

	void displayStudentbySubjectCode (SubjectList& Y, StudentSubjectList& Z) {
		int c;
		cout << "\nEnter subject code: ";
		cin >> c;
		if (Y.search(c) >= 0) {
			int r[MAX_STUDENT];
			int n = Z.searchStudentRoll (c, r);
			cout << n << "students found.";
			for (int i = 0; i < n; i++)
				list[search(r[i])].showData();
		}
		else
			cout << "\nStudent does not exist.";
	}
};

void SubjectList::displaySubjectbyStudentRoll (StudentList& X, StudentSubjectList& Z) {
		int r;
		cout << "\nEnter student roll: ";
		cin >> r;
		if (X.search(r) >= 0) {
			int c[MAX_SUBJECT];
			int n = Z.searchSubjectCode (r, c);
			cout << n << "subjects found.";
			for (int i = 0; i < n; i++)
				list[search(c[i])].showData();
		}
		else
			cout << "\nStudent does not exist.";
	}

class Menu {
public:
	static void operations () {
		StudentList X;
		SubjectList Y;
		StudentSubjectList Z;
		char h = 'n';
		do {
			int ch, op;
			cout << "\n1.Add Subject 2. Add Student 3. Display Subjects by Student Roll 4. Display Students by Subject Code\nEnter your choice: ";
			cin >> ch;
			switch(ch) {
				case 1: Y.addSubject(); break;
				case 2: X.addStudent(Y, Z); break;
				case 3: Y.displaySubjectbyStudentRoll(X, Z); break;
				case 4: X.displayStudentbySubjectCode(Y, Z); break;
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