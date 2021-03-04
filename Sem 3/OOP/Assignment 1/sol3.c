#include <stdio.h>
#include <stdlib.h>

void print_2d_array_pta (int (*q)[], int r, int c) {
	int (*p)[c] = q;
	printf("The array[%d][%d] is: \n", r, c);
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
}

void print_2d_array_aop (int** p, int r, int c) {
	printf("The array[%d][%d] is: \n", r, c);
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
}

void pointer_to_array (int r, int c) {
	int (*p)[c];
	p = (int (*)[]) malloc (r * c * sizeof(int));
	printf("Enter the elements: ");
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			scanf("%d", *(p + i) + j);
	print_2d_array_pta (p, r, c);
	free (p);
}

void array_of_pointers (int r, int c) {
	int* p[r];
	printf("Enter the elements: ");
	for (int i = 0; i < r; i++){
		p[i] = (int*) malloc (c * sizeof(int));
		for (int j = 0; j < c; j++)
			scanf("%d", *(p + i) + j);
	}
	print_2d_array_aop (p, r, c);
	for (int i = 0; i < r; i++)
		free (p[i]);
}
int main () {
	int r, c, ch;
	printf("Enter no of rows and columns: ");
	scanf ("%d %d", &r, &c);
	void (*func_ptr[]) (int, int) = {pointer_to_array, array_of_pointers};
	printf("Implement using 1. Pointer to array 2. Array of Pointers\nEnter your choice: ");
	scanf("%d", &ch);
	if(ch == 1 || ch == 2)
		func_ptr[ch - 1] (r, c);
	else
		printf("Wrong input.\n");
	return 0;
}