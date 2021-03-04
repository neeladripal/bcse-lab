#include <iostream>
#include <map>
using namespace std;

class Batch {
public:
	static void Operations () {
		map <int, float> m;
		char h = 'n';
		int ch, roll;
		float score;
		do {
			printf("1. Add Score 2. Display Score by Roll 3. Display List\nChoose your option: ");
			cin >> ch;
			switch (ch) {
				case 1:
					// enter value of roll
					cout << "Enter roll: ";
					cin >> roll;

					// if roll is not found, add the score to the map using roll as key
					if (m.find(roll) != m.end())
						cout << "Roll already exists.\n";
					else {
						cout << "Enter score: ";
						cin >> score;
						m[roll] = score;
					}
					break;

				case 2:
					// enter value of roll
					cout << "Enter roll: ";
					cin >> roll;

					// if roll is found, display score from map using roll
					if (m.find(roll) != m.end())
						cout << "Score: " << m[roll] << "\n";
					else
						cout << "Roll does not exist.\n";
					break;

				case 3:
					if (!m.empty()) {
						cout << "List of Students -->\n";
						for (map <int, float>::iterator it = m.begin(); it != m.end(); it++)
							cout << "Roll: " << it -> first << "\tScore: " << it -> second << "\n";
					}
					else
						cout << "List is empty.\n";
					break;

				default:
					cout << "Wrong Choice.\n";
			}
			cout << "Do you want to continue (y/n) ? ";
			cin >> h;
		} while (h == 'y' || h == 'Y');
	}
};

int main () {
	Batch::Operations();
	return 0;
}














// class Student {
// 	int roll;
// 	string name;
// 	float score;
// public:

// 	Student (int r = -1, string n = "", float s = 0) () : roll(r), name(n), score (s) {}

// 	void showData () {
// 		cout << "Roll number: " << roll << " Name: " << name  << " Score: " << score << "\n";
// 	}
 
// 	int retRoll () {
// 		return roll;
// 	}

// 	string retName () {
// 		return name;
// 	}

// 	float retScore () {
// 		return score;
// 	}

// 	bool operator == (const Student& s) const {
// 		return (roll == s.roll);
// 	}
// };