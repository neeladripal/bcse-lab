#include <stdio.h>

// function to merge two sorted arrays
void merge (int* a, int na, int* b, int nb, int* c) {
	int i = 0, j = 0, k = 0;

	// add the lower elements first to c
	while (i < na && j < nb)
		if (a[i] < b[i])
			c[k++] = a[i++];
		else
			c[k++] = b[j++];
		
	// if some elements are left in a or b, append them to c
	while (i < na)
		c[k++] = a[i++];
	while (j < nb)
		c[k++] = b[j++];
}

int main () {
	int a[100], b[100], c[200];
	int na, nb;

	printf ("Enter first array -->\n");
	printf ("Enter number of terms: ");
	scanf ("%d", &na);
	if (na > 0) {
		printf ("Enter elements in increasing order of value: ");
		for (int i = 0; i < na; i++)
			scanf ("%d", &a[i]);
	}

	printf ("Enter second array -->\n");
	printf ("Enter number of terms: ");
	scanf ("%d", &nb);
	if (nb > 0) {
		printf ("Enter elements in increasing order of value: ");
		for (int i = 0; i < nb; i++)
			scanf ("%d", &b[i]);
	}

	if (na + nb > 0) {
		merge (a, na, b, nb, c);
		printf ("Merged Array: ");
		for (int i = 0; i < na + nb; i++)
			printf ("%d ", c[i]);
		printf ("\n");
	}
	else
		printf ("Both arrays are Null.\n");
	return 0;
}