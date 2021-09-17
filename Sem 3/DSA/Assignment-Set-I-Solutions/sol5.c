#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LEN 10
#define MAX 100000

/* function to generate a random string */
void get_random_string (char t[]) {
	for (int i = 0; i < LEN; i++)
		t[i] = 'A' + rand() % 26;
	t[LEN] = '\0';
}

int main () {
	char a[MAX][LEN + 1];
	// set the seed for srand ()
	srand (time (NULL));
	
	for (int i = 0; i < MAX; i++) {
		char t[LEN + 1]; // create a temp array
		get_random_string (t); // get a random string
		
		//check for repetition
		int flag = 1;
		for (int j = 0; j < i; j++)
			if (strcmp(t, a[j]) == 0)
				flag = 0;
		
		// if duplicates not found, store the string in array
		if (flag)
			strcpy (a[i], t);
		else
			i--;
	}

	FILE *fp = fopen ("random_strings.txt", "w");

	if (fp == NULL) {
		printf ("File could not be opened.");
		exit (0);
	}

	// store the strings in a file one string per line
	for (int i = 0; i < MAX; i++)
		fprintf (fp, "%s\n", a[i]);

	fclose (fp);
	return 0;
}