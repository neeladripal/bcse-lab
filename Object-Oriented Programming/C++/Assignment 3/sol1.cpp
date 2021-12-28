#include <iostream>
using namespace std;

#define MAX_VALUE(x, y) ((x) >= (y) ? (x) : (y))

int main() {
	int a, b;
	printf("Enter two numbers: ");
	scanf("%d %d", &a, &b);
	printf("Maximum: %d\n", MAX_VALUE(a, b));
	return 0;
}