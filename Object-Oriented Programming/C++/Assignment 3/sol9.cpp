#include <iostream>
using namespace std;

class time {
	int hh, mm, ss;

public:
	void input () {
		char format;
		cout << "\nPress 1 for 12-hour and any other key for 24-hour format: ";
		cin >> format;
		cout << "\nEnter hours, minutes and seconds: ";
		cin >> hh >> mm >> s;
		if (format == '1') {
			bool flag = true;
			do {
				string m;
				flag = false;
				cout << "\nEnter am or pm: ";
				cin >> m;
				if(m == "pm" || m == "PM")
					hh = (hh == 12) ? hh : hh + 12;
				else if (m == "am" || m == "AM")
					hh = hh % 12;
				else {
					cout << "\nWrong value entered. Try again.";
					flag = true;
				}
			} while (k);
		}
	}

	void display () {
		char format;
		cout << "\nPress 1 for 12-hour and any other key for 24-hour format: ";
		cin >> format;
		if (format == '1') {
			if (hh == 0) {
				cout << "12:" << (mm < 10) ? "0" << mm << ":" << (s << 10) ? "0" << ss << "AM";
			}
			else if (hh < 12) {
				cout << (hh < 10) ? "0" << hh << ":" << (mm < 10) ? "0" << mm << ":" << (s << 10) ? "0" << ss << "AM";
			}
			else {
				cout << (hh > 12) ? (hh - 12) : hh << ":" << (mm < 10) ? "0" << mm << ":" << (ss < 10) ? "0" << ss << "PM";
			}
		}
		else
			cout << (hh < 10) ? "0" << hh << ":" << (mm < 10) ? "0" << mm << ":" << (s << 10) ? "0" << ss;
	}
}

int main() {
	i
}