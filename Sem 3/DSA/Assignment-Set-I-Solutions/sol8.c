#include <stdio.h>
#include <string.h>

int main () {
	char name[31];

	// take name as input
	printf ("Enter name: ");
	scanf (" %[^\n]", name);

	// initialise the big integer as an empty string
	char large_int[62] = "";

	for (int i = 0; name[i] != '\0'; i++) {
		char temp[4];
		// create a temp string to store ASCII value of ith index
		sprintf (temp, "%d", (int) name[i]);

		// append the temp string to the big integer
		strcat (large_int, temp);
	}

	// print the large integer
	printf("\nConverted integer = %s", large_int);

	int len = strlen (large_int);

	// cut the integer into two halves
	int left_half[31], right_half[31];
	int p =0, q =0;
	for (int i = 0; i < len; i++)
		if (i < len/2)
			left_half[p++] = large_int[i] - '0';
		else
			right_half[q++] = large_int[i] - '0';


	// Now add the two halves
	int sum[32], reverse_sum[32];
	int k =0, carry = 0;

	// Add the indexes from back end of two halves until one of the number goes out of index
	while (p && q) {
		int s = left_half[--p] + right_half[--q] + carry;
		reverse_sum[k++] = s % 10;
		carry = s / 10;
	}

	// Add the carry to the part of the right half still left
	while (q) {
		int s = right_half[--q] + carry;
		reverse_sum[k++] = s % 10;
		carry = s / 10;
	}

	// If there is carry, push it to the back of the array
	if (carry)
		reverse_sum[k++] = carry;

	// As we pushed the result to the back iteratively, we have the reversed form of the sum
	printf ("\nSum of two halves = ");
		for (int i = 0; i < k; i++) {
		sum[i] = reverse_sum[k - i - 1];
		printf("%d", sum[i]);
	}

	// Take a 4-digit prime number as input
	int P;
	printf ("\nEnter a 4-digit prime number: ");
	scanf ("%d", &P);
	int x = 1, rem = 0;

	// Apply modular multiplication to x and modular addition to rem
	for (int i = 0; i < k; i++) {
		rem += (reverse_sum[i] * x) % P;
		rem %= P;
		x = (x * 10) % P;
	}

	printf ("Remainder when divided by %d = %d\n", P, rem);
	return 0;
}