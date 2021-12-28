#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100

// Function to calculate the length of a name
int name_length (char n[]) {
	int l = 0;
	for (int i = 0; n[i] != '\0'; i++)
		if (n[i] != ' ')
			l++;
	return l;
}

// Function to sort the array 
void sort (char (*arr)[31], int n) {
	char temp[31];
    // Sorting strings using bubble sort 
    for (int i = 0; i < n - 1; i++)
    	for (int j = 0; j < n - i -1; j++)
    		if (strcmp(arr[j], arr[j+1]) > 0) {
    			strcpy(temp, arr[j]);
    			strcpy(arr[j], arr[j+1]);
    			strcpy(arr[j+1], temp); 
            }
}

int main () {
	FILE *fp = fopen ("names.txt", "r");
	if (fp == NULL) {
		printf ("File could not be opened.");
		exit (0);
	}

	char names[MAX][31];
	int n = 0;

	// Get the array of names from file
	while (!feof(fp)) {
		fscanf(fp, " %[^\n]", names[n++]);
	}

	fclose (fp);

	int M = 0, m = INT_MAX, index_M = -1, index_m = -1;

	for (int i = 0; i < n; i++) {
		int slen = name_length (names[i]);

		// find the largest name
		if (slen > M) {
			M = slen;
			index_M = i;
		}

		// find the smallest name
		if (slen < m) {
			m = slen;
			index_m = i;
		}
	}

	printf ("Smallest name (length):- %s (%d)\n", names[index_m], m);
	printf ("Largest name (length):- %s (%d)\n", names[index_M], M);

	// Sort the given names
	sort (names, n);

	// Open the second file
	fp = fopen ("sorted_names.txt", "w");
	if (fp == NULL) {
		printf ("Second file could not be opened.");
		exit (0);
	}

	// Store the names in sorted order in second file
	for (int i = 0; i < n; i++)
		fprintf (fp, "%s\n", names[i]);

	fclose (fp);
	return 0;
}