#include <stdio.h>
#include <stdlib.h>
#include "stringadt.h"

int main() {
	String a, b, c;
	int val, i, j;
	char h = 'n';
	do {
		int ch;
		printf("\nString Operations -->\n1. Display length of a string.\n2. Compare two strings lexicographically.\n3. Concatenate two strings.\n4. Return a substring of a string.\nEnter your choice: ");
		scanf("%d", &ch);
		switch (ch) {
			case 1:
				printf("\nEnter the string: ");
				a = input ();
				printf ("\nLength of the entered string is %d.", length(a));
				clear (&a);
				break;
			case 2:
				printf("\nEnter the first string: ");
				a = input ();
				printf("\nEnter the second string: ");
				b = input ();
				val = compare (a, b);
				if (val == 0)
					printf("\nBoth the strings are equal.");
				else if (val == 1)
					printf("\nFirst string is lexicographically greater.");
				else if (val == -1)
					printf("\nSecond string is lexicographically greater.");

				clear(&a);
				clear(&b);
				break;
			case 3:
				printf("\nEnter the first string: ");
				a = input ();
				printf("\nEnter the second string: ");
				b = input ();
				c = concat (a, b);
				printf ("\nConcatenated string: ");
				display (c);
				clear (&a);
				clear (&b);
				clear (&c);
				break;
			case 4:
				printf("\nEnter the string: ");
				a = input();
				printf ("\nLength of the entered string is %d.", length(a));
				printf ("\nEnter starting index of substring (0-based): ");
				scanf ("%d", &i);
				printf ("\nEnter length of the substring: ");
				scanf ("%d", &j);
				b = substr (a, i, j);
				if (isNull (b))
					printf ("\nSubstring is Null.");			
				else
					printf ("\nSubstring Requested: ");
					display (b);
				clear (&a);
				clear (&b);
				break;
			default:
				printf ("\nWrong Choice.");
		}
		printf ("\nDo you want to continue (y/n) ? ");
		scanf (" %c", &h);
	} while (h == 'y' || h == 'Y');
	return 0;
}