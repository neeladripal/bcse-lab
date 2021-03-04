#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 31

char** name_allocation (int n) {
	char **c = (char **) malloc (n * sizeof(char *));
	for (int i = 0; i < n; i++)
		c[i] = (char*) malloc (MAX_NAME_LENGTH * sizeof(char));
	return c;
}

int* age_allocation (int n) {
	return (int *) malloc (n * sizeof(int));
}

void input_data (char **name, int *age, int n) {
	for (int i = 0; i < n; i++) {
		printf ("Enter name of person %d: ", i + 1);
		scanf (" %[^\n]", name[i]);
		printf ("Enter age of person %d: ", i + 1);
		scanf ("%d", &age[i]);
	}
}

void sort_data_by_age (char **name, int *age, int n) {
	for (int i = 0; i < n; i++)
		for(int j = 0; j < n-i-1; j++)
			if(age[j] > age[j+1]) {
				int t = age[j];
				age[j] = age[j+1];
				age[j+1] = t;
				char c[31];
				strcpy (c, name[j]);
				strcpy (name[j], name[j+1]);
				strcpy (name[j+1], c);
			}
}

void display (char **name, int *age, int n) {
	printf("No. of persons: %d\n", n);
	for (int i = 0; i < n; i++) {
		printf("Person %d, Name: %s, Age: %d\n", i + 1, name[i], age[i]);
	}
}

void delete_data (char **name, int *age, int n) {
	for (int i = 0; i < n; i++)
		free (name[i]);
	free (name);
	free (age);
	printf("End of program. Memory de-allocated successfully.\n");
}

int main () {
	int n;
	printf ("Enter no of persons: ");
	scanf ("%d", &n);
	char **name = name_allocation (n);
	int *age = age_allocation (n);
	input_data (name, age, n);
	printf("Before sorting,\n");
	display (name, age, n);
	sort_data_by_age (name, age, n);
	printf("After sorting,\n");
	display (name, age, n);
	delete_data (name, age, n);
	return 0;
}