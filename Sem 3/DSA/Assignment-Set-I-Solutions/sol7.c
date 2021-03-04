#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 8
#define L_NUM 10
#define L_LEN 9

int main () {
	int prime [MAX];
	printf ("Enter %d four-digit prime numbers: ", MAX);
	for (int i = 0; i < MAX; i++)
		scanf("%d", &prime[i]);

	int L[L_NUM];

	srand (time(NULL));

	// Generate list of big integers
	for (int i = 0; i < L_NUM; i++) {
		L[i] = (rand() % 9) + 1;
		for (int j = 1; j < L_LEN; j++)
			L[i] = L[i] * 10 + (rand() % 10);
	}

	// Tabulate the values
	printf ("Prime Numbers ->");
	for (int j = 0; j < MAX; j++)
		printf ("%10d", prime[j]);
	printf ("\n");

	for (int i = 0; i < 100; i++)
		printf ("-");
	printf ("\n");

	for (int i = 0; i < L_NUM; i++) {
		printf ("%15d ", L[i]);
		for (int j = 0; j < MAX; j++) {
			int r = L[i] % prime[j];
			printf ("%10d", r);
		}
		printf ("\n");
	}

	return 0;
}