#include <iostream>
using namespace std;

int& max (int &p, int &q) {
	return (p >= q)? p : q;
}

int main() {
	int a, b;
	printf("Enter two values: ");
	scanf("%d %d", &a, &b);
	int x = max (a, b);
	// int &x = max (a, b);
	printf("a = %d b = %d x = %d", a, b, x);
	x = 77;
	printf("a = %d b = %d x = %d", a, b, x);
	return 0;
}