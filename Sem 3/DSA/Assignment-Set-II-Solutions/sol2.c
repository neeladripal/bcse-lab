#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"

int main () {
	sparse A[MAX_TERMS], B[MAX_TERMS], C[MAX_TERMS];
	char h = 'n';
	do {
		int ch;
		printf ("Sparse Matrix Operations-->\n1. Transpose a matrix 2. Add two matrices 3. Multiply two matrices\nEnter your choice: ");
		scanf ("%d", &ch);
		printf ("Enter a sparse matrix -->\n");
		getMatrix (A);
		if (ch == 2 || ch == 3) {
			printf ("Enter second sparse matrix -->\n");
			getMatrix (B);
		}
		switch (ch) {
			case 1: 
				transpose (A, B); 
				displayMatrix (B);
				break;
			case 2:
				add (A, B, C);
				displayMatrix (C);
				break;
			case 3:
				mult (A, B, C);
				displayMatrix (C);
				break;
			default: printf ("Wrong choice.\n");
		}
		printf ("Do you want to continue (y/n) ?");
		scanf (" %c", &h);
	} while (h == 'y' || h == 'Y');
	return 0;
}