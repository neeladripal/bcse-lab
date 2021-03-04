#include<stdio.h>
int main() {
	int x;
	int *p = &x;
	int** pp = &p;
	printf("Enter value: ");
	scanf("%d", p);
	printf("Value entered: %d %d\n", *p, *pp);
	return 0;
}