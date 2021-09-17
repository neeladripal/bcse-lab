#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "listWithSentinel.h"
#include "listWithoutSentinel.h"

int menu() {
	int ch;
	printf("\nList Operations (1-based indexing) -->");
	printf("\n1. Insert an element in the list.");
	printf("\n2. Get the length of the list.");
	printf("\n3. Get ith element of the list.");
	printf("\n4. Display the list.");
	printf("\n5. Update an element of the list.");
	printf("\n6. Delete ith element of the list.");
	printf("\n7. Search for an element in the list.");
	printf("\nEnter your choice: ");
	scanf(" %d", &ch);
	return ch;
}

int main() {
	int ch;
	printf("\nSelect what kind of list you want to use 1. Sentinel Version 2. Without Sentinel Version : ");
	scanf(" %d", &ch);
	if (ch == 1) { // list with sentinel
		List l;
		initList (&l);
		int i, val;
		char h = 'n';
		do {
			switch (menu()) {
				case 1:
					printf("\nEnter position of insertion: ");
					scanf(" %d", &i);
					printf("\nEnter the value to be inserted: ");
					scanf(" %d", &val);
					insertIth(&l, i, val);
					break;
				case 2:
					printf("\nLength of list: %d", lengthList(l));
					break;
				case 3:
					printf("\nEnter index of element whose value you want to get: ");
					scanf(" %d", &i);
					val = getIth(l, i);
					if (val != SENTINEL) {
						printf("\nValue at index %d: %d", i, val);
					}
					break;
				case 4:
					displayList(l);
					break;
				case 5:
					printf("\nEnter index of element to be updated: ");
					scanf(" %d", &i);
					printf("\nEnter the new value: ");
					scanf(" %d", &val);
					updateIth(&l, i, val);
					break;
				case 6:
					printf("\nEnter index of element to be deleted: ");
					scanf(" %d", &i);
					deleteIth(&l, i);
					break;
				case 7:
					printf("\nEnter value of element to be searched: ");
					scanf(" %d", &val);
					if (search(l, val)) {
						printf("\nElement found.");
					} else {
						printf("\nElement not found.");
					}
					break;
				case 8:
					exit(0);
					break;
				default:
					printf("\nInvalid Choice.");
					break;
			}
			printf("\nDo you want to continue (y/n)? ");
			scanf (" %c", &h);
		} while (h == 'y' || h == 'Y');
	}

	else if (ch == 2) { // list without sentinel
		ListNS l;
		initListNS (&l);
		int i, val;
		char h = 'n';
		do {
			switch (menu()) {
				case 1:
					printf("\nEnter position of insertion: ");
					scanf(" %d", &i);
					printf("\nEnter the value to be inserted: ");
					scanf(" %d", &val);
					insertIthNS (&l, i, val);
					break;
				case 2:
					printf("\nLength of list: %d", lengthListNS (l));
					break;
				case 3:
					printf("\nEnter index of element whose value you want to get: ");
					scanf(" %d", &i);
					val = getIthNS (l, i);
					if (val != SENTINEL) {
						printf("\nValue at index %d: %d", i, val);
					}
					break;
				case 4:
					displayListNS (l);
					break;
				case 5:
					printf("\nEnter index of element to be updated: ");
					scanf(" %d", &i);
					printf("\nEnter the new value: ");
					scanf(" %d", &val);
					updateIthNS (&l, i, val);
					break;
				case 6:
					printf("\nEnter index of element to be deleted: ");
					scanf(" %d", &i);
					deleteIthNS (&l, i);
					break;
				case 7:
					printf("\nEnter value of element to be searched: ");
					scanf(" %d", &val);
					if (searchNS (l, val)) {
						printf("\nElement found.");
					} else {
						printf("\nElement not found.");
					}
					break;
				case 8:
					exit(0);
					break;
				default:
					printf("\nInvalid Choice.");
					break;
			}
			printf("\nDo you want to continue (y/n)? ");
			scanf (" %c", &h);
		} while (h == 'y' || h == 'Y');
	}

	else
		printf("\nWrong choice Exiting...");
	return 0;
}
