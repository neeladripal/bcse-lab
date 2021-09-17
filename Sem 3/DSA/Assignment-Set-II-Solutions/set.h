#define MAX 100

typedef struct {
	int size;
	int data[MAX];
} set;

void initSet (set* S) {
	S -> size = 0;
}

int findItem (set* S, int item) {
	for (int i = 0; i < S->size; ++i) {
		if (S->data[i] == item)
			return 1;
	}
	return 0;
}

void insertItem (set* S, int item) {
	int size = S -> size;
	if (!findItem (S, item)) {
		if (size < MAX) {
			S -> data[size] = item;
			++(S -> size);
		}
	}
	else
		printf ("\nItem already present in set.");
}

void removeItem (set* S, int item) {
	int size = S -> size;

	if (size <= 0) 
		printf("Empty set.\n");

	else if (!findItem (S, item))
		printf("Data not present in the given set.\n");
	
	else {
		int index = -1;
		for (int i = 0; i < S->size; ++i) {
			if (S->data[i] == item) {
				index = i;
				break;
			}
		}
		for (int i = index; i < S->size - 1; ++i) {
			S->data[i] = S->data[i + 1];
		}
		--(S -> size);
		printf("\nSuccessfully removed.");
	}
}

void display (set* S) {
	printf("\nThe set contents are : {");
	for (int i = 0; i < S->size; ++i) {
		printf("%d, ", S->data[i]);
	}
	printf("}\n");
}

set unionOf (set* S1, set* S2) {
	set S;
	initSet (&S);
	for (int i = 0; i < S1->size; ++i) {
		insertItem (&S, S1->data[i]);
	}
	for (int i = 0; i < S2->size; ++i) {
		insertItem (&S, S2->data[i]);
	}
	return S;
}

set intersectionOf (set* S1, set* S2) {
	set S;
	initSet (&S);
	for (int i = 0; i < S1->size; ++i) {
		if (findItem (S2, S1->data[i])) {
			insertItem (&S, S1->data[i]);
		}
	}
	return S;
}

set differenceOf (set* S1, set* S2) {
	set S;
	initSet (&S);
	for (int i = 0; i < S1->size; ++i) {
		if (!findItem (S2, S1->data[i])) {
			insertItem (&S, S1->data[i]);
		}
	}
	return S;
}

int isSubset (set* S1, set* S2) {
	for (int i = 0; i < S1->size; ++i) {
		if (!findItem (S2, S1->data[i])) {
			return 0;
		}
	}
	return 1;
}