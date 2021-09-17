#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to compare two integer values 
int myCompare_int(const void* a, const void* b) {
    // setting up rules for comparison 
    return *(int*)a - *(int*)b; 
} 
  
// Function to sort the array 
void sort_int(int* arr, int n) { 
    // calling qsort function to sort the array 
    // with the help of Comparator 
    qsort(arr, n, sizeof(int), myCompare_int); 
} 

// Function to compare two floating-point values
int myCompare_float(const void* a, const void* b) {
    // setting up rules for comparison 
    return *(float*)a - *(float*)b; 
} 
  
// Function to sort the array 
void sort_float(float* arr, int n) { 
    // calling qsort function to sort the array 
    // with the help of Comparator 
    qsort(arr, n, sizeof(float), myCompare_float); 
} 

// Function to compare two words
int myCompare_word(const void* a, const void* b) {
    // setting up rules for comparison 
    return strcmp((char*)a, (char*)b); 
} 
  
// Function to sort the array 
void sort_word(char arr[][31], int n) { 
    // calling qsort function to sort the array 
    // with the help of Comparator 
    qsort(arr, n, 31 * sizeof(char), myCompare_word); 
} 

// Function for binary search in an array of integer values
void binary_search_int(int *a, int n, int x) {
  sort_int (a, n); // sort the array of integers
  int left = 0, right = n; 
  while (left <= right) {
  	int mid = left + (right - left) / 2;
  	if(a[mid] == x) {
  		printf ("Found %d by binary search.\n", a[mid]);
  		return;
  	}
  	if(a[mid] > x)
  		right = mid - 1;
  	else
  		left = mid + 1;
  }
  printf ("Not found by binary search.\n");
}

// Function for linear search in an array of integer values
void linear_search_int(const int *a, int n, int x) {
  for (int i = 0; i < n; ++i)
    if (a[i] == x) {
    	printf ("Found %d by linear search.\n", a[i]);
  		return;
    }
  printf ("Not found by linear search.\n");
}

// Function for binary search in an array of floating-point values
void binary_search_float(float *a, int n, float x, float e) {
  sort_float (a, n); // sort the array of floating point numbers
  int left = 0, right = n; 
  while (left <= right) {
  	int mid = left + (right - left) / 2;
  	if (fabs (a[mid] - x) <= e) {
  		printf ("Found %f by binary search.\n", a[mid]);
  		return;
  	}
  	if(a[mid] > x + e)
  		right = mid - e;
  	else
  		left = mid + e;
  }
  printf ("Not found by binary search.\n");
}

// Function for linear search in an array of floating-point values
void linear_search_float(const float *a, int n, float x, float e) {
  for (int i = 0; i < n; ++i)
    if (fabs(a[i] - x) <= e) {
    	printf ("Found %f by linear search.\n", a[i]);
  		return;
    }
  printf ("Not found by linear search.\n");
}

// Function for binary search in an array of words
void binary_search_word (char a[][31], int n, char *x) {
  sort_word (a, n); // sort the array of words
  int left = 0, right = n; 
  while (left <= right) {
  	int mid = left + (right - left) / 2;
  	if(strcmp (a[mid], x) == 0) {
  		printf ("Found %s by binary search.\n", a[mid]);
  		return;
  	}
  	if(strcmp (a[mid], x) > 0)
  		right = mid - 1;
  	else
  		left = mid + 1;
  }
  printf ("Not found by binary search.\n");
}

// Function for linear search in an array of words
void linear_search_word (const char a[][31], int n, char *x) {
  for (int i = 0; i < n; ++i)
    if (strcmp (a[i], x) == 0) {
    	printf ("Found %s by linear search.\n", a[i]);
  		return;
    }
  printf ("Not found by linear search.\n");
}

// Driver Code
int main () {
	int op;
	printf ("1. Integer 2. Floating point number 3. Word\nEnter choice: ");
	scanf ("%d", &op);
	if(op == 1) {
		int a[100], n, x;
		printf ("Enter no of integers: ");
		scanf ("%d", &n);
		printf ("Enter integers: ");
    // take the array as input
		for (int i = 0; i < n; i++)
			scanf ("%d", &a[i]);
    // take the element to be searched
		printf ("Enter the integer to be searched: ");
		scanf ("%d", &x);
		linear_search_int (a, n, x); // call to linear search function
		binary_search_int (a, n, x); // call to binary search search function
	}
  else if (op == 2) {
		float a[100], x, epsilon;
		int n;
		printf ("Enter no of floating point numbers: ");
		scanf ("%d", &n);
		printf ("Enter floating point numbers: ");
    // take the array as input
		for (int i = 0; i < n; i++)
			scanf ("%f", &a[i]);
    // take the floating-point number to be searched
		printf ("Enter the floating point number to be searched: ");
		scanf ("%f", &x);
    // take the error value allowed
		printf ("Enter the error margin: ");
		scanf ("%f", &epsilon);
		linear_search_float (a, n, x, epsilon); // call to linear search function
		binary_search_float (a, n, x, epsilon); // call to binary search search function
    }
  else if (op == 3) {
		int n;
		char a[100][31], x[31];
		printf ("Enter no of words: ");
		scanf ("%d", &n);
		printf ("Enter words: ");
    // take the array as input
		for (int i = 0; i < n; i++)
			scanf ("%s", a[i]);
    // take the word to be searched
		printf ("Enter the word to be searched: ");
		scanf ("%s", x);
		linear_search_word (a, n, x); // call to linear search function
		binary_search_word (a, n, x); // call to binary search search function
  }
  else
		printf ("Wrong choice.\n");
	return 0;
}