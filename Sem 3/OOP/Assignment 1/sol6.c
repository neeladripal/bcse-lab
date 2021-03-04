#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[31];
	int age;
}person;

person* data_allocation (int n) {
	person* list = (person*) malloc (n*sizeof(person));
	return list;
}

void input_data (person* list, int n) {
	for (int i = 0; i < n; i++) {
		printf ("Enter name of person %d: ", i + 1);
		scanf (" %[^\n]", list[i].name);
		printf ("Enter age of person %d: ", i + 1);
		scanf ("%d", &list[i].age);
	}
}

void sort_data_by_age (person* list, int n) {
	for (int i = 0; i < n; i++)
		for(int j = 0; j < n-i-1; j++)
			if(list[j].age > list[j+1].age) {
				person t = list[j];
				list[j] = list[j+1];
				list[j+1] = t;
			}
}

void display (person* list, int n) {
	printf("No. of persons: %d\n", n);
	for (int i = 0; i < n; i++) {
		printf("Person %d, Name: %s, Age: %d\n", i + 1, list[i].name, list[i].age);
	}
}

void delete_data (person *list, int n) {
	free (list);
	printf("End of program. Memory de-allocated successfully.\n");
}

int main () {
	int n;
	printf ("Enter no of persons: ");
	scanf ("%d", &n);
	person* list = data_allocation (n);
	input_data (list, n);
	printf("Before sorting,\n");
	display (list, n);
	sort_data_by_age (list, n);
	printf("After sorting,\n");
	display (list, n);
	delete_data (list, n);
	return 0;
}