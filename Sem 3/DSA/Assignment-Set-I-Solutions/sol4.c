#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* function for swapping values of two variables */
void swap (int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

/* function to return pointer to base address of a dynamically
allocated array containing n random integers from 1 to n */
int* generate_random (int n) {
	int* p = (int*) malloc (n * sizeof(int)); // create a dynamic array
	// store values from 1 to n
	for (int i = 0; i < n; i++)
		p[i] = i + 1;
	// set the seed for srand() function
	srand(time(0));

	for (int i = 0; i < n; i++) {
		// generate random index from 0 to n-1
		int r = rand() % n;
		// swap values in ith index and rth index
		swap (&p[i], &p[r]);
	}
	return p;
}

// Driver Code
int main () {
	int n = 100000;
	// random points to the array containing random integers
	int* random = generate_random (n);

	FILE *fp = fopen ("random_numbers.txt", "w");

	if (fp == NULL) {
		printf ("File could not be created");
		free (random);
		exit (0);
	}

	for (int i = 0; i < n; i++) {
		int t = random[i], l = -1;

		// calculate length of ith random integer
		while (t) {
			l++;
			t /= 10;
		}

		// retrive the digits of the number from left end and store it in file
		int divisor = pow (10, l);
		while (divisor) {
			char c = '0' + (random[i] / divisor) % 10;
			fputc (c, fp);
			divisor /= 10;
		}
		fputc ('\n', fp);
	}
	fclose (fp);
	free (random);
	return 0;
}