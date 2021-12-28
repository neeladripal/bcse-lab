#include <iostream>
using namespace std;

double tax_amount (double income, double tax_rate = 10) {
	return (income * tax_rate) / 100;
}

int main () {
	double income, tax_rate;
	printf ("Enter income and tax rate (in percentage): ");
	scanf ("%lf %lf", &income, &tax_rate);
	printf("Tax amount: %lf", tax_amount(income, tax_rate));
	return 0;
}