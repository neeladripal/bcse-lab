#include <iostream>
using namespace std;

struct student {
	int roll;
	float score;
	void take_input (void);
	void show_data (void);
};

void student:: take_input() {
	cout << "Enter roll: ";
	cin >> roll;
	cout << "Enter score: ";
	cin >> score;
}

void student:: show_data() {
	cout << "Roll: " << roll << " Score: " << score << endl;
}

void modify (student &s, float score) {
	s.score = score;
}

void show (student s) {
	cout << "After modification, Roll: " << s.roll << " Score: " << s.score << endl;
}

int main () {
	student s;
	s.take_input();
	s.show_data();
	modify (s, 98.2);
	show (s);
	return 0;
}