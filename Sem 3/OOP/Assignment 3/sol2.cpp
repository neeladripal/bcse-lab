#include <iostream>
using namespace std;

inline int product (int a, int b) {
	return a * b;
}

int main () {
	int x, y;
	printf("Enter two numbers: ");
	scanf("%d %d", &x, &y);
	printf("Product: %d\n", product(a, b));
	return 0;
}