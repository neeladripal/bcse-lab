#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main () {
	char h = 'n';
	do {
		int ch, e;
		float c;
		poly A, B, X;
		printf ("\nPolynomial Operations -->");
		printf ("\n1. Check if a polynomial is Zero polynomial\n2. Find coefficient of an exponent\n3. Multiply polynomial by a constant\n4. Display degree of a polynomial\n5. Add two polynomials\n6. Multiply two polynomials\nEnter your choice: ");
		scanf ("%d", &ch);
		printf("\nEnter a polynomial -->\n");
		if (input (&A))
			ch = 7;
		if (ch == 5 || ch == 6) {
			printf ("\nEnter second polynomial -->\n");
			if (input (&B))
				ch = 7;
		}
		switch (ch) {
			case 1:
				if (isZero(A))
					printf ("\nZero Polynomial.");
				else
					printf ("\nNot Zero Polynomial.");
				break;
			case 2:
				printf("\nEnter exponent: ");
				scanf ("%d", &e);
				printf("\nCoefficient of x^%d = %f", e, coef(A, e));
				break;
			case 3:
				printf("\nEnter constant: ");
				scanf ("%f", &c);
				cMult (A, c);
				printf ("\nResultant Polynomial: ");
				display (A);
				break;
			case 4:
				printf("\nDegree: %d\n", degree (A));
				break;
			case 5:
				add (&X, A, B);
				printf ("\nResultant Polynomial: ");
				display (X);
				break;
			case 6:
				mult (&X, A, B);
				printf ("\nResultant Polynomial: ");
				display (X);
				break;
			case 7:
				printf ("\nInvalid input value.");
				break;
			default:
				printf ("\nWrong Choice.");
		}
		printf ("\nDo you want to continue (y/n)? ");
		scanf (" %c", &h);
	} while (h == 'y' || h == 'Y');
	return 0;
}