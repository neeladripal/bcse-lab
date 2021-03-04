#include <stdio.h>

// compute fibonacci term by recursive way
long long fibRecursive (int n) {
	if (n == 1 || n == 2)
		return (n - 1);
	else
		return fibRecursive (n - 1) + fibRecursive (n - 2);
}

// compute fibonacci term by iterative way
long long fibIterative (int n) {
	if (n == 1 || n == 2)
        return (n - 1);
    
    long long previous = 0, current  = 1;

    for (int i = 2; i < n; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current;
}

// Driver Code
int main () {
	int n;
	printf ("Enter number (> 0): ");
	scanf ("%d", &n);
	printf ("By iterative method, %dth Fibonacci Number = %lld\n", n, fibIterative(n));
	printf ("By recursive method, %dth Fibonacci Number = %lld\n", n, fibRecursive(n));
	return 0;
}