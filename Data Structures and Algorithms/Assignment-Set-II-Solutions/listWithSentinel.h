#define MAX_LEN 100			// maximum size of a list
#define SENTINEL INT_MIN	// defining sentinel as the minimum value an integer type variable can hold

typedef struct {
	int elements[MAX_LEN];	// array of elements in the list
} List;

// function to initialize an empty list
void initList (List* L) {
	L -> elements[0] = SENTINEL;	// setting first element as sentinel to mark end of list
}

// function to return the number of elements in the list
int lengthList (List L) {
	int len = 0;
	while (L.elements[len] != SENTINEL)		// while element at len isn't sentinel
		++len;
	return len;
}

// function to return the ith value of the list
int getIth (List L, int i) {
	int len = lengthList (L);	// get the length of the given list
	i--;	// convert to 0-based index
	if (i >= 0 && i < len)		// check validity of index
		return L.elements[i];
	else {
		printf ("Index out of bound.\n");
		return SENTINEL;
	}
}

// function to display the list
void displayList (List L) {
	int len = lengthList (L);	// get the length of the given list
	int ch;
	printf("How would you prefer to view the list? 1.Original Order 2. Reverse Order\n");
	scanf("%d", &ch);
	switch (ch) {
		case 1:
			printf("List in original order: ");
			for (int i = 0; i < len; i++) {		// traverse in original order
				printf("%d ", L.elements[i]);
			}
			printf("\n");
			break;
		case 2:
			printf("List in reverse order: ");
			for (int i = len - 1; i >= 0; i--) {	// traverse in reverse order	
				printf("%d ", L.elements[i]);
			}
			printf("\n");
			break;
		default:
			printf("Wrong Choice.\n");
	}
}

// function to update value of ith index
void updateIth (List* L, int i, int val) {
	int len = lengthList (*L);		// get the length of the given list
	i--;	// convert to 0-based index
	if (i >= 0 && i < len)			// check validity of index
		L -> elements[i] = val; 	// update the value
	else
		printf ("Index out of bounds.\n");
}

// function to insert a value at ith index in the list
void insertIth (List* L, int i, int val) {
	int len = lengthList (*L);		// get the length of the given list
	if (len == MAX_LEN - 1)			// check if space is there to insert an element
		printf("List space exceeded.\n");
	else {
		if (i >= 1 && i <= len + 1) {	// check validity of index for insertion
			i--;	// convert to 0-based index
			for (int j = len; j > i; j--)
				L -> elements[j] = L -> elements[j - 1];	// shift elements towards right by an index, starting from ith index

			L -> elements[i] = val;		// insert the value;
			L -> elements[len + 1] = SENTINEL;	// update end of the list
		}
		else
			printf("Out of bounds. Enter a proper index for insertion.\n");
	}
}

// function to remove the value at ith index in the list
void deleteIth (List* L, int i) {
	int len = lengthList (*L);	// get the length of the given list
	if (i >= 1 && i <= len) {	// check validity of the index for deletion
		i--;	// convert to 0-based index
		for (int j = i; j < len; j++)
			L -> elements[j] = L -> elements[j + 1];	// shift elements towards left by an index, starting from ith index
	}
	else
		printf("Out of bounds. Enter a proper index for deletion.\n");
}

// function to search for a value in the given list
int search (List L, int val) {
	int len = lengthList (L);		// get the length of the given list
	for (int i = 0; i < len; i++)	// traverse the list
		if (L.elements[i] == val)
			return 1;
	return 0;
}