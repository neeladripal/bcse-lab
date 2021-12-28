#include <iostream>
using namespace std;

void f(int x, int y) {
	printf("inside f(int, int)");
}

void f(char x, int y) {
	printf("inside f(char, int)");
}

int main() {
	f(6, 'a');
	f('a', 'b');
	f(7.6f, 9.2f);
	return 0;
}