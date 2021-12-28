#include <iostream>
using namespace std;

void swap (int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}

int main() {
 	int x, y;
 	printf ("x = ");
 	scanf ("%d", &x);
 	printf ("y = ");
 	scanf ("%d", &y);
 	swap (x, y);
 	printf ("x = %d y = %d", x, y);
 	return 0;
 }