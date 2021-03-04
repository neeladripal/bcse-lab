#include <iostream>
using namespace std;

class Node {
	int data;
	Node *next;
	friend class LinkedList;
public:
	Node (int x) {
		data = x;
		next = NULL;
	}
};

class LinkedList {
	Node *head;
	int count;

	bool node_created (Node *p) {
		if (p == NULL) {
			cout << "Node cannot be created.\n";
			return false;
		}
		return true;
	}
public:

	LinkedList () {
		head = NULL;
		count = 0;
	}

	int node_count () {
		return count;
	}

	void insert (int pos) {
		int x;
		cout << "Enter Value: ";
		cin >> x;
		Node *newNode = new Node(x);

		if (node_created(newNode)) {
			count++;
			if (pos == 1) {
				newNode -> next = head;
				head = newNode;
			}
			else {
				Node *cur = head, *prev = head;
				for (int k = 1; (k < pos) && (cur != NULL); k++) {
					prev = cur;
					cur = cur -> next;
				}
				prev -> next = newNode;
				newNode -> next = cur;
			}
			cout << "Record added successfully.\n";
		}
	}

	void display () {
		if (head == NULL) {
			printf("Database is empty.\n");
			return;
		}
		cout << "List: ";
		for (Node *cur = head; cur != NULL; cur = cur -> next)
			cout << cur -> data << " ";
		cout << "Number of records: " << count << "\n";
	}

	void del (int pos) {
		if (head == NULL) {
			cout << "Database is empty.\n";
			return;
		}

		Node *cur = head;
		if (pos == 1) {
			head = head -> next;
			delete cur;
			count--;
		}
		else {
			Node *prev = NULL;
			for (int k = 1; (k < pos) && (cur != NULL); k++) {
				prev = cur;
				cur = cur -> next;
			}
			if (cur == NULL) {
				cout << "Position does not exist.\n";
			}
			else {
				prev -> next = cur -> next;
				delete cur;
				count--;
			}
		}
	}

	void delete_all () {
		while (head != NULL) {
			Node *auxiliaryNode = head;
			head = head -> next;
			delete auxiliaryNode;
		}
		count = 0;
		cout << "Memory freed successfully.\n";
	}
};

int main() {
	LinkedList L;
	char c = 'n';
	do {
		int ch, r;
		cout << "1. Add a node\n2. Display list\n3. Delete a node\n4. Delete list\nEnter your choice: ";
		cin >> ch;
		switch (ch) {
			case 1: L.insert (1); break;
			case 2:	L.display (); break;
			case 3: L.del (1); break;
			case 4: L.delete_all (); break;
			default: cout << "Wrong choice.\n";
		}
		cout << "Press y to go to main menu. Press any other key to exit.\n";
		cin >> c;
	} while (c == 'y' || c == 'Y');
	L.delete_all();
	return 0;
}