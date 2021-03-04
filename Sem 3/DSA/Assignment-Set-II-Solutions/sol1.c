#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main () {
	char h = 'n';
	do {
		int ch, e;
		float c;
		poly A, B, X;
		printf ("Polynomial Operations -->\n");
		printf ("1. Check if a polynomial is Zero polynomial\n2. Find coefficient of an exponent\n3. Multiply polynomial by a constant\n4. Display degree of a polynomial\n5. Add two polynomials\n6. Multiply two polynomials\nEnter your choice: ");
		scanf ("%d", &ch);
		printf("Enter a polynomial -->\n");
		input (&A);
		if (ch == 5 || ch == 6) {
			printf ("Enter second polynomial -->\n");
			input (&B);
		}
		switch (ch) {
			case 1:
				if (isZero(A))
					printf ("Zero Polynomial.\n");
				else
					printf ("Not Zero Polynomial.\n");
				break;
			case 2:
				printf("Enter exponent: ");
				scanf ("%d", &e);
				printf("Coefficient of x^%d = %f\n", e, coef(A, e));
				break;
			case 3:
				printf("Enter constant: ");
				scanf ("%f", &c);
				cMult (A, c);
				display (A);
				break;
			case 4:
				printf("Degree: %d\n", degree (A));
				break;
			case 5:
				add (A, B, &X);
				display (X);
				break;
			case 6:
				mult (A, B, &X);
				display (X);
				break;
			default:
				printf ("Wrong Choice.\n");
		}
		printf ("Do you want to continue (y/n)? ");
		scanf (" %c", &h);
	} while (h == 'y' || h == 'Y');
	return 0;
}