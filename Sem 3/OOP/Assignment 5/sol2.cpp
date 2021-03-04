#include <iostream>
#define MAX_BOOKS 100
#define MAX_COPIES 10
#define MAX_STUDENT 100
#define MAX_FACULTY 100
#define MAX_ENTRIES 1000

using namespace std;

class Copy {
	int sno;
	int availability;
	friend class Book;

public:
	Copy () {
		sno = -1;
		availability = 0;
	}

	void createNewCopy (int& c) {
		sno = ++c;
		availability = 1;
	}

	void updateCopy () {
		availability = (availability + 1) % 2;
	}
};

class Book {
	int bookid;
	char title[41];
	char author[31];
	char publisher[31];
	float price;
	Copy copylist[MAX_COPIES];
	int copycount;

public:
	Book () {
		bookid = -1;
		copycount = 0;
	}

	int getid () const {
		return bookid;
	}

	void addCopy () {
		int n;
		cout << "Enter number of copies: ";
		cin >> n;
		for (int i = 0; i < n; i++)
			copylist[copycount].createNewCopy(copycount);
	}

	void getData (int id) {
		bookid = id;
		cout << "Enter book details -->\n";
		cout << "Title: ";
		scanf (" %[^\n]", title);
		cout << "Author: ";
		scanf (" %[^\n]", author);
		cout << "Publisher: ";
		scanf (" %[^\n]", publisher);
		cout << "Price: ";
		cin >> price;
		addCopy();
		cout << "Book added successfully.\n";
	}

	int getAvailableCopyCount () {
		int a = 0;
		for (int i = 0; i < copycount; i++)
			if (copylist[i].availability)
				a++;
		return a;
	}

	void showData () {
		cout << "Book with id " << bookid << "details -->\n";
		cout << "Title: " << title << "\nAuthor: " << author << "\nPublisher: " << publisher << "\nPrice: " << price;
		cout << "\nNo. of copies: " << getAvailableCopyCount();	
	}

	int issueCopy () {
		if (getAvailableCopyCount()) {
			for (int i = 0; i < copycount; i++)
				if (copylist[i].availability) {
					copylist[i].updateCopy();
					return copylist[i].sno;
				}
		}
		else
			cout << "No copy of book (id: " << bookid << ") is available.\n";
		return 0;
	}

	void returnCopy (int sno) {
		for (int i = 0; i < copycount; i++)
			if (copylist[i].sno == sno) {
				copylist[i].updateCopy();
				return;
			}
	}
};

class BookList {
	static Book list[MAX_BOOKS];
	static int count;

public:

	static int searchBook (int id) {
		for (int i = 0; i < count; i++)
			if (list[i].getid() == id)
				return i;
		return -1;
	}

	static void addBook () {
		int id, index;
		cout << "Enter book id (>0): ";
		cin >> id;
		if (id <= 0) {
			cout << "Book id must be greater than 0.\n";
			return;
		}
		if ((index = searchBook(id)) >= 0) {
			char op = 'y';
			cout << "Book already exists. Want to add more copies (y/n) ?";
			cin >> op;
			if (op == 'y' || op == 'Y') {
				list[index].addCopy();
				cout << "Copies added successfully to book (id: " << id << ").\n";
			}
		}
		else
			list[count++].getData (id);
	}

	static int issueBook (int id) {
		int index = searchBook (id);
		if (index < 0) {
			cout << "Book not found.\n";
			return 0;
		}
		else {
			int sno = list[index].issueCopy();
			if(sno) {
				cout << "Book issued. Serial Number: " << sno << "\n";
				return sno;
			}
			else
				return 0;
		}
	}

	static void returnBook (int id, int sno) {
		int index = searchBook (id);
		list[index].returnCopy(sno);
	}
};

class Member {
	int memberid;
	static int membercount;
protected:
	char name[31];
	char email[41];
	char address[101];
public:
	int getid () const {
		return memberid;
	}

	virtual int checkIssueEligibilty () = 0;
	virtual void updateOnIssue () = 0;
	virtual void updateOnReturn () = 0;

	void getData () {
		memberid = ++membercount;
		cout << "Enter more details -->\n";
		cout << "Enter name: ";
		scanf (" %[^\n]", name);
		cout << "Enter email: ";
		scanf (" %[^\n]", email);
		cout << "Enter address: ";
		scanf (" %[^\n]", address);
	}
};

class Student : public Member {
	int noofbooksissued;
	int maxbooks;
public:
	Student () {
		noofbooksissued = 0;
		maxbooks = 2;
	}

	int checkIssueEligibilty () {
		return maxbooks - noofbooksissued;
	}

	void updateOnIssue () {
		noofbooksissued++;
	}

	void updateOnReturn () {
		noofbooksissued--;
	}
};

class StudentList {
	static Student list[MAX_STUDENT];
	static int count;
public:

	static int searchStudent (int id) {
		for (int i = 0; i < count; i++)
			if (list[i].getid() == id)
				return i;
		return -1;
	}

	static void addStudent () {
		list[count].getData();
		cout << "Student added successfully with member id " << list[count].getid() << " .\n";
		count++;
	}

	static int issueBook (int mid, int bid) {
		int index = searchStudent(mid);
		if (index >= 0)
			if (list[index].checkIssueEligibilty()) {
				int s = BookList::issueBook (bid);
				if (s) {
					list[index].updateOnIssue();
					return s;
				}
			}
			else
				cout << "Maximum limit reached.\n";
		else
			cout << "Student does not exist.\n";
		return 0;
	}

	static void returnBook (int mid) {
		int index = searchStudent(mid);
		if (index >= 0)
			list[index].updateOnReturn();
	}
};

class Faculty : public Member {
	int noofbooksissued;
	int maxbooks;
public:
	Faculty () {
		noofbooksissued = 0;
		maxbooks = 10;
	}

	int checkIssueEligibilty () {
		return maxbooks - noofbooksissued;
	}

	void updateOnIssue () {
		noofbooksissued++;
	}

	void updateOnReturn () {
		noofbooksissued--;
	}
};

class FacultyList {
	static Faculty list[MAX_FACULTY];
	static int count;
public:

	static int searchFaculty (int id) {
		for (int i = 0; i < count; i++)
			if (list[i].getid() == id)
				return i;
		return -1;
	}

	static void addFaculty () {
		list[count].getData();
		cout << "Faculty added successfully with member id " << list[count].getid() << " .\n";
		count++;
	}

	static int issueBook (int mid, int bid) {
		int index = searchFaculty(mid);
		if (index >= 0)
			if (list[index].checkIssueEligibilty()) {
				int s = BookList::issueBook (bid);
				if (s) {
					list[index].updateOnIssue();
					return s;
				}
			}
			else
				cout << "Maximum limit reached.\n";
		else
			cout << "Faculty does not exist.\n";
		return 0;
	}

	static void returnBook (int mid) {
		int index = searchFaculty(mid);
		if (index >= 0)
			list[index].updateOnReturn();
	}
};

class Transaction {
	char dateoftransaction[11];
	int memberid;
	int bookid;
	int sno;
	int returned;
	friend class TransactionList;
public:
	void getData (char t) {
		cout << "Enter memberid: ";
		cin >> memberid;
		cout << "Enter bookid: ";
		cin >> bookid;
		if (t == 'r') {
			cout << "Enter serial number: ";
			cin >> sno;
		}
		returned = 0;
	}

	int checkReturnEligibilty (Transaction T) {
		if (memberid == T.memberid && bookid == T.bookid && sno == T.sno && returned == 0)
			return 1;
		else
			return 0;
	}
};

class TransactionList {
	static Transaction list[MAX_ENTRIES];
	static int count;
public:

	static void addEntry () {
		Transaction T;
		T.getData('i');
		int p = -1, q = -1;
		if ((p = StudentList::issueBook(T.memberid, T.bookid)) > 0) {
			cout << "Enter date of transaction (dd-mm-yyyy): ";
			cin >> T.dateoftransaction;
			T.sno = p;
			list[count++] = T;
			cout << "Issue request successful.\n";
		}

		else if ((q = FacultyList::issueBook(T.memberid, T.bookid)) > 0) {
			cout << "Enter date of transaction (dd-mm-yyyy): ";
			cin >> T.dateoftransaction;
			T.sno = q;
			list[count++] = T;
			cout << "Issue request successful.\n";
		}
	}

	static void updateEntry () {
		Transaction T;
		T.getData('r');
		for (int i = 0; i < count; i++)
			if (list[i].checkReturnEligibilty(T)) {
				BookList::returnBook (T.bookid, T.sno);
				StudentList::returnBook (T.memberid);
				FacultyList::returnBook (T.memberid);
				list[i].returned = 1;
				cout << "Return request successful.\n";
				return;
			}
		cout << "Record not found. Return request unsuccessful.\n";
	}
};

	Book BookList::list[MAX_BOOKS];
	int BookList::count;
	int Member::membercount;
	Student StudentList::list[MAX_STUDENT];
	int StudentList::count;
	Faculty FacultyList::list[MAX_FACULTY];
	int FacultyList::count;
	Transaction TransactionList::list[MAX_ENTRIES];
	int TransactionList::count;

int main () {
	char h = 'n';
	do {
		int ch, op;
		cout << "\n1.Add Book 2. Add Student 3. Add Faculty 4. Issue 5. Return\nEnter your choice: ";
		cin >> ch;
		switch(ch) {
			case 1: BookList::addBook(); break;
			case 2: StudentList::addStudent(); break;
			case 3: FacultyList::addFaculty(); break;
			case 4: TransactionList::addEntry(); break;
			case 5: TransactionList::updateEntry(); break;
			default: cout << "Wrong choice.\n";
		}
		cout << "\nDo you want to continue (y/n) ? ";
		cin >> h;
	} while (h == 'y' || h == 'Y');
}