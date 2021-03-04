#include <iostream>
#include <fstream>

using namespace std;

class Copy {
	int sno;			// serial number of a copy
	int availability;	// 1 - available, 0 - not available
	friend class Book;

public:
	Copy () {
		sno = -1;
		availability = 0;
	}

	void createNewCopy (int& c) {		// accept copy count as parameter
		sno = ++c;		// set serial number and update copy count
		availability = 1;
	}

	void updateCopy () {
		availability = (availability + 1) % 2;		// toggle availability
	}
};

class Book {
	int bookid;		// unique identifier for a book
	char title[41];
	char author[31];
	char publisher[31];
	float price;
	Copy copylist[MAX_COPIES];		// array of copies of the book
	int copycount;					// no of copies

public:
	Book () {
		bookid = -1;
		copycount = 0;
	}

	int getId () const {	// accessor function to get book id
		return bookid;
	}

	void addCopy () {		// function to add copies of a book
		int n;
		cout << "Enter number of copies: ";
		cin >> n;

		if (n < 0) {
			cout << "Number of copies must be non-negative.\n";
			n = 0;
		}

		// update serial number and availability for each copy
		for (int i = 0; i < n; i++)
			copylist[copycount].createNewCopy(copycount);
	}

	void getData (int id) {		// input details of a book
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
		addCopy();		// add copies to the book
		cout << "Book added successfully.\n";
	}

	int getAvailableCopyCount () {		// get available copy count of a book
		int a = 0;
		for (int i = 0; i < copycount; i++)
			if (copylist[i].availability)	// check if the serial number is available
				a++;
		return a;
	}

	void showData () {		// dispaly details of a book
		cout << "\nBook(id: " << bookid << ") details -->";
		cout << "\nTitle: " << title << "\nAuthor: " << author << "\nPublisher: " << publisher << "\nPrice: " << price;
		cout << "\nNo. of copies: " << getAvailableCopyCount() << "\n";
	}

	int issueCopy () {		// issue a copy of a book
		if (getAvailableCopyCount()) {
			for (int i = 0; i < copycount; i++)

				// if a copy is found, update its availability
				if (copylist[i].availability) {
					copylist[i].updateCopy();
					return copylist[i].sno;		// return the serial number
				}
		}
		else
			cout << "No copy of book (id: " << bookid << ") is available.\n";
		return 0;	// in case no copy is available
	}

	void returnCopy (int sno) {		// return a copy of a book
		for (int i = 0; i < copycount; i++)

			// match with the serial number and update availabilty
			if (copylist[i].sno == sno) {
				copylist[i].updateCopy();
				return;
			}
	}
};

class BookFile {
	char fn[31];	// name of file where list of books is stored
public:

	BookFile (char fname[]) {
		strcpy (fn, fname);
	}

	int searchBook (int id) {	// searches for a book within a file
		int k = 0;
		Book B;
		fstream f (fn, ios::in | ios::binary);
		while (!f.eof()) {
			f.read ((char *)&B, sizeof(Book));
			k++;
			if (B.getId() == id)	// returns index if found
				break;
		}
		if (f.eof())
			k = 0;		// returns 0 if not found
		f.close();
		return k;
	}

	void addBook () {
		int id;			// input book id and check if it is valid
		cout << "\nEnter book id (>0): ";
		cin >> id;
		if (id <= 0) {
			cout << "Book id must be greater than 0.\n";
			return;
		}

		Book B;
		int index = searchBook (id);	// search in the file for the book with this book id

		if (index) {

			// if book is already present, support is provided to add more copies
			char op = 'y';
			cout << "Book already exists. Want to add more copies (y/n) ? ";
			cin >> op;
			
			if (op == 'y' || op == 'Y') {

				fstream f (fn, ios::in | ios :: ate | ios::binary);
				f.seekg ((index - 1) * sizeof(Book), ios::beg);
				f.read ((char*)&B, sizeof(Book));
				
				// add no of copies in the book
				B.addCopy();
				
				f.seekp ((index - 1) * sizeof(Book), ios::beg);
				f.write ((char*)&B, sizeof(Book));
				f.close ();
				
				cout << "Copies added successfully to book (id: " << id << ").\n";
			}
		}
		else {

			// add a new book
			B.getData (id);
			ofstream f (fn, ios::app | ios::binary);
			f.write ((char*)&B, sizeof(Book));
			f.close ();
		}
	}

	void displayBooks () {	// display list of books
		cout << "\nBook List -->\n";
		Book B;
		ifstream f (fn, ios::in | ios::binary);

		while (!f.eof()) {
			f.read ((char*)&B, sizeof(Book));
			B.showData ();
		}
		
		f.close();
	}

	int issueBook (int id) {		// issue a book
		
		int index = searchBook (id);	// search in the file for the book with this book id
		if (index == 0) {
			cout << "Book not found.\n";
			return 0;
		}
		else {		// if book found, issue a copy if available
			Book B;
			
			fstream f (fn, ios::in | ios :: ate | ios::binary);
			f.seekg ((index - 1) * sizeof(Book), ios::beg);
			f.read ((char*)&B, sizeof(Book));
			
			int sno = B.issueCopy();	// issue a book to get the serial number of copy issued

			if (sno) {		// if any available copy is found
				cout << "Book issued. Serial Number: " << sno << "\n";
				
				f.seekp ((index - 1)*sizeof(Book), ios::beg);
				f.write ((char*)&B, sizeof(Book));
				f.close ();
				
				return sno;		// return the serial number
			}
			else {
				f.close();
				return 0;		// if not available, return 0
			}
		}
	}

	void returnBook (int id, int sno) {		// return copy of a book
		
		int index = searchBook (id);	// search in the file for the book with this book id
		
		Book B;
		fstream f (fn, ios::in | ios :: ate | ios::binary);
		f.seekg ((index - 1)*sizeof(Book), ios::beg);
		f.read ((char*)&B, sizeof(Book));
		
		B.returnCopy(sno);		// return the copy to the book using its serial number
		
		f.seekp ((index - 1)*sizeof(Book), ios::beg);
		f.write ((char*)&B, sizeof(Book));
		f.close ();
	}

};

class Member {
	int memberid;	// unique identifier for a member
	char name[31];
	char email[41];
	char address[101];
	int noofbooksissued;
	int maxbooks;
	char type;		// s - student, f -faculty

public:

	int getId () const {	// accessor function to get member id
		return memberid;
	}

	int checkIssueEligibilty () {		// check if maximum limit is not reached
		return maxbooks - noofbooksissued;
	}

	void updateOnIssue () {		// on issue, increment no of books issued
		noofbooksissued++;
	}

	void updateOnReturn () {	// on return, decrement no of books issued
		noofbooksissued--;
	}

	void getData (char c, int& mcount) {		// input details of a member
		memberid = ++mcount;		// assign member id and update member count
		cout << "Enter more details -->\n";
		cout << "Enter name: ";
		scanf (" %[^\n]", name);
		cout << "Enter email: ";
		scanf (" %[^\n]", email);
		cout << "Enter address: ";
		scanf (" %[^\n]", address);
		noofbooksissued = 0;	// no of books issued is 0
		if (c == 's')
			maxbooks = 2;		// maximum no of books issued by a student
		else
			maxbooks = 10;		// maximum no of books issued by a faculty
	}

	void showData () {		// print details of a member
		cout << "\nMember Id: " << memberid << " Type: ";
		if (type == 's')
			cout << "Student";
		else
			cout << "Faculty";
		cout << "\nName: " << name << "\nEmail: " << email << "\nAddress: " << address;
		cout << "\nNumber of books issued: " << noofbooksissued << "\n";
	}
};

class MemberFile {		// name of file where list of members is stored
	char fn[31];
	int membercount;		// no of members
public:

	MemberFile (char fname[]) {
		strcpy (fn, fname);			// copy filename

		// update the value of member count
		ifstream f (fn, ios::in | ios::binary);
		Member M;
		f.seekg (0, ios::end);
		f.read ((char*)&M, sizeof(Member));
		membercount = M.getId();
		f.close();
	}

	int searchMember (int id) {		// searches for a member within a file
		int k = 0;
		Member M;
		fstream f (fn, ios::in | ios::binary);
		
		while (!f.eof()) {
			f.read ((char*)&M, sizeof(Member));
			k++;
			if (M.getId() == id)	// returns index if found
				break;
		}
		
		if (f.eof())
			k = 0;		// returns 0 if not found
		f.close();
		return k;
	}

	void addStudent () {	// add a new student to the file
		Member M;
		M.getData('s', membercount);
		
		ofstream f (fn, ios::app | ios::binary);
		f.write ((char*)&M, sizeof(Member));
		f.close ();

		cout << "Student added successfully with member id " << M.getId() << " .\n";
	}

	void addFaculty () {	// add a new faculty to the file
		Member M;
		M.getData('f', membercount);
		
		ofstream f (fn, ios::app | ios::binary);
		f.write ((char*)&M, sizeof(Member));
		f.close ();
		
		cout << "Faculty added successfully with member id " << M.getId() << " .\n";
	}

	void displayMembers () {	// display list of members
		cout << "Member List -->\n";
		Member M;
		ifstream f (fn, ios::in | ios::binary);

		while (!f.eof()) {
			f.read ((char*)&M, sizeof(Member));
			M.showData ();
		}

		f.close();
	}

	int issueBook (int mid, int bid, BookFile &BF) {

		int index = searchMember(mid);		// search in the file for the member with this member id
		if (index) {	// if member is found

			Member M;
			fstream f (fn, ios::in | ios :: ate | ios::binary);
			f.seekg ((index - 1)*sizeof(Member), ios::beg);
			f.read ((char*)&M, sizeof(Member));

			if (M.checkIssueEligibilty()) {		// if number of books issued is less than the maximum limit

				int s = BF.issueBook (bid);		// get the serial number of issued copy
				if (s) {						// if there is a copy available

					M.updateOnIssue();			// increment no of books issued

					f.seekp ((index - 1)*sizeof(Member), ios::beg);
					f.write ((char*)&M, sizeof(Member));
					f.close ();
					return s;
				}
			}
			else
				cout << "Maximum limit on number of books issued reached.\n";
			f.close ();
		}
		else
			cout << "Member does not exist.\n";
		return 0;
	}

	void returnBook (int mid) {

		int index = searchMember(mid);		// search in the file for the member with this member id

		Member M;
		fstream f (fn, ios::in | ios :: ate | ios::binary);
		f.seekg ((index - 1)*sizeof(Member), ios::beg);
		f.read ((char*)&M, sizeof(Member));

		M.updateOnReturn();					// decrement no of books issued

		f.seekp ((index - 1)*sizeof(Member), ios::beg);
		f.write ((char*)&M, sizeof(Member));
		f.close ();
	}
};

class Transaction {
protected:
	char dateoftransaction[11];
	int memberid;		// given in transaction slip
	int bookid;			// given in transaction slip
	int sno;			// given in transaction slip
public:
	void getData () {		// get data for transaction slip
		cout << "Enter memberid: ";
		cin >> memberid;
		cout << "Enter bookid: ";
		cin >> bookid;
	}

	void showData () {			// print details of transaction
		cout << "\nDate of Transaction: " << dateoftransaction << "\n";
		cout << "Member Id: " << memberid << "\n";
		cout << "Book Id: " << bookid << "\n";
		cout << "Serial Number: " << sno << "\n";
	}
};

class ReturnTransaction : public Transaction {
public:
	void getData () {		// get data for transaction slip
		Transaction::getData ();
		cout << "Enter serial number: ";
		cin >> sno;			// for return, serial number is needed
	}

	friend class IssueTransaction;
};

class IssueTransaction : public Transaction {
	int returned;
public:
	void getData () {		// get data for transaction slip
		Transaction::getData ();
		returned = 0;		// for issue, returned is set to 0
	}

	void showData () {			// print details of transaction
		Transaction::showData();
		cout << "Returned: ";
		if (returned)
			cout << "Yes\n";
		else
			cout << "No\n";
	}

	int checkReturnEligibilty (ReturnTransaction T) {		// check if transaction slip details are eligible for return
		if (memberid == T.memberid && bookid == T.bookid && sno == T.sno && returned == 0)
			return 1;
		else
			return 0;
	}

	friend class TransactionFile;
};

class TransactionFile {		// name of file where list of transactions is stored
	char fn[31];
public:

	TransactionFile (char fname[]) {
		strcpy (fn, fname);
	}

	void addEntry (MemberFile& MF, BookFile& BF) {
		IssueTransaction IT;	// issue type object
		IT.getData();		// get data for the issue transaction slip

		int p = MF.issueBook(IT.memberid, IT.bookid, BF);		// issue a book

		if (p) {		// if copy is available, serial number is returned
			cout << "Enter date of transaction (dd-mm-yyyy): ";
			cin >> IT.dateoftransaction;
			IT.sno = p;
			
			ofstream f (fn, ios::app | ios::binary);
			f.write ((char*)&IT, sizeof(IssueTransaction));
			f.close ();
			
			cout << "Issue done successfully.\n";
		}
	}

	int searchEntry (ReturnTransaction RT) {		// searches the transaction eligible for return
		int k = 0;
		IssueTransaction IT;
		fstream f (fn, ios::in | ios::binary);

		while (!f.eof()) {
			f.read ((char*)&IT, sizeof(IssueTransaction));
			k++;
			if (IT.checkReturnEligibilty(RT))	// returns index if found
				break;
		}

		if (f.eof())
			k = 0;		// returns 0 if not found
		f.close();
		return k;
	}

	void updateEntry (MemberFile& MF, BookFile& BF) {
		ReturnTransaction RT;
		RT.getData();		// get data for the return transaction slip

		int index = searchEntry (RT);		// search in the file for the transaction given in transaction slip
		if (index) {

			IssueTransaction IT;	// get the corresponding issue object

			fstream f (fn, ios::in | ios :: ate | ios::binary);
			f.seekg ((index - 1) * sizeof(IssueTransaction), ios::beg);
			f.read ((char*)&IT, sizeof(IssueTransaction));

			BF.returnBook (IT.bookid, IT.sno);		// return the book
			MF.returnBook (IT.memberid);			// make neceassary changes in the member associated

			cout << "Enter date of transaction (dd-mm-yyyy): ";
			cin >> IT.dateoftransaction;
			IT.returned = 1;		// update the returnned attribute

			
			f.seekp ((index - 1) * sizeof(IssueTransaction), ios::beg);
			f.write ((char*)&IT, sizeof(IssueTransaction));
			f.close ();

			cout << "Book returned successfully.\n";
			return;
		}
		cout << "Record not found. Return request unsuccessful.\n";
	}

	void displayEntries () {		// display the list of transactions
		cout << "Transaction List -->\n";
		IssueTransaction T;
		ifstream f (fn, ios::in | ios::binary);
		
		while (!f.eof()) {
			f.read ((char*)&T, sizeof(Transaction));
			T.showData ();
		}

		f.close();
	}
};

int main () {
	char h = 'n';
	char bfn[] = "Books.dat";
	char mfn[] = "Members.dat";
	char tfn[] = "Transactions.dat";

	BookFile B (bfn);
	MemberFile M (mfn);
	TransactionFile T (tfn);

	do {
		int ch, op;
		cout << "\n1. Add Book 2. Add Student 3. Add Faculty 4. Issue 5. Return";
		cout << "\n6. Display Book List 7. Display Member List 8. Display Transaction List\nEnter your choice: ";
		cin >> ch;

		switch(ch) {
			case 1: B.addBook(); break;
			case 2: M.addStudent(); break;
			case 3: M.addFaculty(); break;
			case 4: T.addEntry(M, B); break;
			case 5: T.updateEntry(M, B); break;
			case 6: B.displayBooks(); break;
			case 7: M.displayMembers(); break;
			case 8: T.displayEntries(); break;
			default: cout << "Wrong choice.\n";
		}

		cout << "\nDo you want to continue (y/n) ? ";
		cin >> h;
	} while (h == 'y' || h == 'Y');
}