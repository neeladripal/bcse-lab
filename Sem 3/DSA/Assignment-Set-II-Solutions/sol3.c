#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "listWithSentinel.h"
#include "listWithoutSentinel.h"

int menu() {
	int ch;
	printf("List Operations -->\n");
	printf("1. Insert an element in the list.\n");
	printf("2. Get the length of the list.\n");
	printf("3. Get ith element of the list.\n");
	printf("4. Display the list.\n");
	printf("5. Update an element of the list.\n");
	printf("6. Delete ith element of the list.\n");
	printf("7. Search for an element in the list.\n");
	scanf("%d", &ch);
	return ch;
}

int main() {
	int ch;
	printf("Select what kind of list you want to use 1. Sentinel Version 2. Without Sentinel Version : \n");
	scanf("%d", &ch);
	if (ch == 1) { // list with sentinel
		List l;
		initList (&l);
		int i, val;
		char h = 'n';
		do {
			switch (menu()) {
				case 1:
					printf("Enter position of insertion: ");
					scanf("%d", &i);
					printf("Enter the value to be inserted: ");
					scanf("%d", &val);
					insertIth(&l, i, val);
					break;
				case 2:
					printf("Length of list: %d\n", lengthList(l));
					break;
				case 3:
					printf("Enter index of element whose value you want to get: ");
					scanf("%d", &i);
					val = getIth(l, i);
					if (val != SENTINEL) {
						printf("Value at index %d: %d\n", i, val);
					}
					break;
				case 4:
					displayList(l);
					break;
				case 5:
					printf("Enter index of element to be updated: ");
					scanf("%d", &i);
					printf("Enter the new value: ");
					scanf("%d", &val);
					updateIth(&l, i, val);
					break;
				case 6:
					printf("Enter index of element to be deleted: ");
					scanf("%d", &i);
					deleteIth(&l, i);
					break;
				case 7:
					printf("Enter value of element to be searched: ");
					scanf("%d", &val);
					if (search(l, val)) {
						printf("Element found.\n");
					} else {
						printf("Element not found.\n");
					}
					break;
				case 8:
					exit(0);
					break;
				default:
					printf("Invalid Choice.\n");
					break;
			}
			printf("Do you want to continue (y/n)? ");
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
					printf("Enter position of insertion: ");
					scanf("%d", &i);
					printf("Enter the value to be inserted: ");
					scanf("%d", &val);
					insertIthNS (&l, i, val);
					break;
				case 2:
					printf("Length of list: %d\n", lengthListNS (l));
					break;
				case 3:
					printf("Enter index of element whose value you want to get: ");
					scanf("%d", &i);
					val = getIthNS (l, i);
					if (val != SENTINEL) {
						printf("Value at index %d: %d\n", i, val);
					}
					break;
				case 4:
					displayListNS (l);
					break;
				case 5:
					printf("Enter index of element to be updated: ");
					scanf("%d", &i);
					printf("Enter the new value: ");
					scanf("%d", &val);
					updateIthNS (&l, i, val);
					break;
				case 6:
					printf("Enter index of element to be deleted: ");
					scanf("%d", &i);
					deleteIthNS (&l, i);
					break;
				case 7:
					printf("Enter value of element to be searched: ");
					scanf("%d", &val);
					if (searchNS (l, val)) {
						printf("Element found.\n");
					} else {
						printf("Element not found.\n");
					}
					break;
				case 8:
					exit(0);
					break;
				default:
					printf("Invalid Choice.\n");
					break;
			}
			printf("Do you want to continue (y/n)? ");
			scanf (" %c", &h);
		} while (h == 'y' || h == 'Y');
	}

	else
		printf("Wrong choice Exiting...\n");
	return 0;
}
