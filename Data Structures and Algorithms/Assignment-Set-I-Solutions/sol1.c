#include <stdio.h>

// recursive method to compute factorial
long long factRecursive (long long n) {
	if (n < 2)
		return 1;
	else
		return n * factRecursive (n - 1);
}

// iterative method to compute factorial
long long factIterative (long long n) {
	long long f = 1;
	while (n) {
		f = f * n;
		n--;
	}
	return f;
}

// Driver Code
int main () {
	int n;
	printf("Enter number: ");
	scanf ("%d", &n);
	printf ("By Recursive method, %d! = %lld\n", n, factRecursive(n));
	printf ("By Iterative method, %d! = %lld\n", n, factIterative(n));
	return 0;
}