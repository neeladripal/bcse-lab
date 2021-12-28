#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "set.h"

int menu() {
	int op;
	printf("\nSet Operations -->");
	printf("\n1. Insert an item in set A");
	printf("  2. Remove an item from the set A");
	printf("  3. Display set A");
	printf("\n4. Insert an item in set B");
	printf("  5. Remove an item from the set B");
	printf("  6. Display set B");
	printf("\n7. Perform union of A and B");
	printf("\n8. Perform intersection of A and B");
	printf("\n9. Find difference A - B");
	printf("\n10. Check if A is a subset of B");
	printf("\n11. Check if B is a subset of A");
	printf("\nEnter your choice: ");
	scanf(" %d", &op);
	return op;
}

int main () {
	char ch = 'n';
	set A, B, C;
	initSet (&A);
	initSet (&B);
	do {
		int k, op = menu ();
		if (op == 1 || op == 2 || op == 4 || op == 5) {
			printf ("\nEnter item value: ");
			scanf (" %d", &k);
		}
		switch (op) {
			case 1: insertItem (&A, k);
					break;
			case 2: removeItem (&A, k);
					break;
			case 3: display (&A);
					break;
			case 4: insertItem (&B, k);
					break;
			case 5: removeItem (&B, k);
					break;
			case 6: display (&B);
					break;
			case 7: C = unionOf (&A, &B);
					display (&C);
					break;
			case 8: C = intersectionOf (&A, &B);
					display (&C);
					break;
			case 9: C = differenceOf (&A, &B);
					display (&C);
					break;
			case 10:
				if (isSubset (&A, &B))
					printf ("\nA is a subset of B.");
				else
					printf ("\nA is not a subset of B.");
				break;
			case 11:
				if (isSubset (&B, &A))
					printf ("\nB is a subset of A.");
				else
					printf ("\nB is not a subset of A.");
				break;
			default:
				printf ("\nWrong choice.");
		}
		printf ("\nDo you want to continue ? (y/n) ");
		scanf (" %c", &ch);
	} while (ch == 'y' || ch == 'Y');
	return 0;
}