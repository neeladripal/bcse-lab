#include <stdio.h>
#include <stdlib.h>
int main () {
	int n;
	printf("Enter no of elements: ");
	scanf("%d", &n);
	int* p = (int*) malloc (n * sizeof(int));
	printf("Enter the elements: ");
	for(int i = 0; i < n; i++) {
		scanf("%d", p + i);
	}
	printf("Elements are ");
	for(int i = 0; i < n; i++) {
		printf("%d ", *(p + i));
	}
	printf(".\n");
	free(p);
	return 0;
}