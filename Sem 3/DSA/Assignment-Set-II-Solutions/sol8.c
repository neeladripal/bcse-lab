#include <stdio.h>

int isSorted (int* a, int n) {
	if (n == 1 || n == 2)
		return 1;
	for (int i = 2; i < n; i++)
		if ((a[i] - a[i-1]) * (a[i-1] - a[i-2]) < 0)
			return 0;
	return 1;
}

int main () {
	int a[100];
	printf ("Enter number of terms: ");
	scanf ("%d", &n);
	if (n > 0) {
		printf ("Enter elements of the array: ");
		for (int i = 0; i < n; i++)
			scanf ("%d", &a[i]);
		if (isSorted(a, n))
			printf ("Array is sorted.\n");
		else
			printf ("Array is not sorted.\n");
	}
	else
		printf ("Number of terms must be positive.\n");
	return 0;
}