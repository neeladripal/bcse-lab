#include <stdio.h>
#include <stdlib.h>

void accept_dimensions_1D_array (int *nn) {
	printf("Enter no of elements: ");
	scanf("%d", nn);
}

int* memory_allocation_1D_array (int n) {
	int *p = (int*) malloc (n * sizeof(int));
	return p;
}

void accept_values_1D_array (int *p, int n) {
	printf("Enter elements: ");
	for(int i = 0; i < n; i++)
		scanf("%d", p + i);
}

void print_values_1D_array (int *p, int n) {
	printf("1D array[%d]: ", n);
	for(int i = 0; i < n; i++)
		printf("%d ", p[i]);	
}

void accept_dimensions_2D_array (int *rr, int *cc) {
	printf("Enter no of rows and columns: ");
	scanf("%d %d", rr, cc);
}

int (*memory_allocation_2D_array_pta (int r, int c)) [] {
	int (*p)[c] = (int (*)[]) malloc (r * c * sizeof(int));
	return p;
}

void accept_values_2D_array_pta (int (*q)[], int r, int c) {
	int (*p)[c] = q;
	printf("Enter the elements: ");
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++)
			scanf("%d", &p[i][j]);
	}
}

void print_values_2D_array_pta (int (*q)[], int r, int c) {
	int (*p)[c] = q;
	printf("The array[%d][%d] is: \n", r, c);
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
}

int** memory_allocation_2D_array_aop (int r, int c) {
	int *p[r];
	for (int i = 0; i < r; i++)
		p[i] = (int *) malloc (c * sizeof(int));
	return p;
}

void accept_values_2D_array_aop (int **p, int r, int c) {
	printf("Enter elements: ");
	for (int i = 0; i < r; i++)
		for(int j = 0; j < c; j++)
			scanf("%d", *(p+i)+j);
}

void print_values_2D_array_aop (int **p, int r, int c) {
	printf("The array[%d][%d] is: \n", r, c);
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
}

int main () {
	int ch;
	printf("1. 1D array 2. 2D array using pointer to array 3. 2D array using array of pointers\nEnter your choice: ");
	scanf("%d", &ch);
	if (ch == 1) {
		int dim;
		accept_dimensions_1D_array (&dim);
		int *p = memory_allocation_1D_array (dim);
		accept_values_1D_array (p, dim);
		print_values_1D_array (p, dim);
		free(p);
	}

	else if (ch == 2) {
		int r, c;
		accept_dimensions_2D_array (&r, &c);
		int (*p)[c] = memory_allocation_2D_array_pta (r, c);
		accept_values_2D_array_pta (p, r, c);
		print_values_2D_array_pta (p, r, c);
		free (p);
	}

	else if (ch == 3) {
		int r, c;
		accept_dimensions_2D_array (&r, &c);
		int** p = memory_allocation_2D_array_aop (r, c);
		accept_values_2D_array_aop (p, r, c);
		print_values_2D_array_aop (p, r, c);
		for(int i = 0; i < r; i++)
			free (p[i]);
	}

	else
		printf("Wrong Choice");

	return 0;
}