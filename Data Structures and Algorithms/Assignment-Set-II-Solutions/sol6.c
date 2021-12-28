#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// function to calculate minimum value in an array
int minarr (int arr[], int n) {
	int res = arr[0];
	for (int i = 0; i < n; ++i) {
		if (arr[i] < res) 
			res = arr[i];
	}
	return res;
}

// // function to calculate maximum value in an array
int maxarr (int arr[], int n) {
	int res = arr[0];
	for (int i = 0; i < n; ++i)
		if (arr[i] > res) {
			res = arr[i];
	}
	return res;
}

// function to sort an array in ascending order using bubble sort
void sort (int arr[], int n) {
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
}

// function to find the median of an array
int medianarr (int arr[], int n) {
	sort(arr, n);
	int res = arr[(n / 2)];
	return res;
}

int main () {

	int n, k;
	printf("\nEnter no of elements: ");
	scanf("%d", &n);

	int arr[n];
	printf("\nEnter %d elements: ", n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &arr[i]);
	}

	printf("\nEnter sliding window filter size choice (3 / 5 / 7): ");
	scanf("%d", &k);

	if (k == 3 || k == 5 || k == 7) {
		int minfilter[n], maxfilter[n], medianfilter[n];

		for (int i = 0; i < n; ++i) {
			int filter[k], x = 0;

			// build the filter array
			for (int j = i - (k / 2); j <= i + (k / 2); ++j) {
				if (j >= 0 && j < n)
					filter[x] = arr[j];
				else
					filter[x] = 0;
				++x;
			}

			// compute max, min, median values of filter
			minfilter[i] = minarr(filter, k);
			maxfilter[i] = maxarr(filter, k);
			medianfilter[i] = medianarr(filter, k);
		}

		printf ("\nMax filter output: ");
		for (int i = 0; i < n; ++i)
			printf("%d ", maxfilter[i]);

		printf ("\nMin filter output: ");
		for (int i = 0; i < n; ++i)
			printf("%d ", minfilter[i]);

		printf ("\nMedian filter output: ");
		for (int i = 0; i < n; ++i)
			printf("%d ", medianfilter[i]);

		printf("\n");
	}
	else
		printf("\nInvalid filter size entered. Exiting...\n");
	
	return 0;
}