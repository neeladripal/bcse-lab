#include <iostream>
using namespace std;

void f(int x) {
	printf("inside f(int)");
}

void f(float x) {
	printf("inside f(float)");
}

int main () {
	f(7);
	f('a');
	f(5.7f);
	f(5.7);
	return 0;
}