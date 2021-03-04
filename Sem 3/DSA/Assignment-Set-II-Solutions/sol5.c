#include <stdio.h>
#include <stdlib.h>
#include "stringadt.h"

int main() {
	String a, b, c;
	int val, i, j;
	char h = 'n';
	do {
		int ch;
		printf("String Operations -->\n1. Display length of a string.\n2. Compare two strings lexicographically.\n3. Concatenate two strings.\n4. Return a substring of a string.\n");
		scanf("%d", &ch);
		switch (ch) {
			case 1:
				a = input ();
				printf ("Length of the entered string is %d.\n", length(a));
				clear (&a);
				break;
			case 2:
				a = input ();
				b = input ();
				val = compare (a, b);
				if (val == 0)
					printf("Both the strings are equal.\n");
				else if (val == 1)
					printf("First string is lexicographically greater.\n");
				else if (val == -1)
					printf("Second string is lexicographically greater.\n");

				clear(&a);
				clear(&b);
				break;
			case 3:
				a = input ();
				b = input ();
				c = concat (a, b);
				printf ("Concatenated string: ");
				display (c);
				clear (&a);
				clear (&b);
				clear (&c);
				break;
			case 4:
				a = input();
				printf ("Length of the entered string is %d.\n", length(a));
				printf ("Enter starting index of substring (0-based): ");
				scanf ("%d", &i);
				printf ("Enter length of the substring: ");
				scanf ("%d", &j);
				b = substr (a, i, j);
				if (isnull (b))
					printf ("Substring is Null.\n");			
				else
					printf ("Substring Requested: ");
					display (b);
				clear (&a);
				clear (&b);
				break;
			default:
				printf ("Wrong Choice.\n");
		}
		printf ("Do you want to continue (y/n) ?");
		scanf (" %c", &h);
	} while (h == 'y' || h == 'Y');
	return 0;
}