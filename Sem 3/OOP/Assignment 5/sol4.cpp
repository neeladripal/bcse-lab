#include <iostream>
using namespace std;

class Cricketer {
	char name[31];
	char dob[11];
	int matchesplayed;
public:
	void getData ();
	void showData ();
};

class Batsman: virtual public Cricketer {
	int totalruns;
	float battingaverage;
public:
	void getData ();
	void showData ();
};

class Bowler: virtual public Cricketer {
	int wickets;
	float economy;
public:
	void getData ();
	void showData ();
};

class DoubleWicketPair {
	Batsman Bat;
	Bowler Ball;
public:
	void getData ();
	void showData ();
};

class AllRounder: public Batsman, public Bowler {
public:
	void getData ();
	void showData ();
};
