#define MAX_TERMS 1000

typedef struct {
	float coeff;
	int expo;
} polynomial;

polynomial terms[MAX_TERMS];
int terms_avail = 0;

typedef struct {
	int start;
	int finish;
} poly;

int compare (const void *X, const void *Y) {
	int a = ((polynomial*)X) -> expo, b = ((polynomial*)Y) -> expo;
	if (a > b)
		return -1;
	else if (a < b)
		return 1;
	else
		return 0;
}

int isZero (poly A) {
	return (A.finish < A.start);
}

float coef (poly A, int e) {
	for (; A.start <= A.finish; A.start++) {
		if (terms[A.start].expo == e)
			return terms[A.start].coeff;
	}
	return 0;
}

void attach (float c, int e) {
	if (terms_avail >= MAX_TERMS) {
		printf ("Too many terms in the polynomial.\n");
		exit (0);
	}
	terms[terms_avail].coeff = c;
	terms[terms_avail++].expo = e;
}

void add (poly A, poly B, poly* X) {
	float coefficient;
	X -> start = terms_avail;
	while (A.start <= A.finish && B.start <= B.finish)
		switch(compare((const void*)(terms + A.start), (const void*)(terms + B.start))) {
			case 1:
				attach(terms[B.start].coeff, terms[B.start].expo);
				B.start++;
				break;
			case 0:
				coefficient = terms[A.start].coeff + terms[B.start].coeff;
				if (coefficient)
					attach (coefficient, terms[A.start].expo);
				A.start++;
				B.start++;
				break;
			case -1:
				attach(terms[A.start].coeff, terms[A.start].expo);
				A.start++;
				break;
		}
	for (; A.start <= A.finish; A.start++)
		attach(terms[A.start].coeff, terms[A.start].expo);
	for (; B.start <= B.finish; B.start++)
		attach(terms[B.start].coeff, terms[B.start].expo);
	X -> finish = terms_avail - 1;
}

void update (float coefficient, int exponent, poly* X) {
	for (int i = X -> start; i <= X -> finish; i++)
		if (terms[i].expo == exponent) {
			terms[i].coeff += coefficient;
			return;
		}
	attach (coefficient, exponent);
	X -> finish = terms_avail - 1;
}

void mult (poly A, poly B, poly* X) {
	X -> start = terms_avail;
	X -> finish = terms_avail - 1;
	for (int i = A.start; i <= A.finish; i++)
		for (int j = B.start; j <= B.finish; j++) {
			float coefficient = terms[i].coeff * terms[j].coeff;
			int exponent = terms[i].expo + terms[j].expo;
			if (coefficient)
				update (coefficient, exponent, X);
		}
	qsort (terms + X -> start, X -> finish - X -> start + 1, sizeof(polynomial), compare);
}

void cMult (poly A, float c) {
	for (int i = A.start; i <= A.finish; i++)
		terms[i].coeff *= c;
}

int degree (poly A) {
	if (isZero(A))
		return -1;
	else
		return terms[A.start].expo;
}

void input (poly* A) {
	A -> start = terms_avail;
	int n;
	printf ("Enter number of terms: ");
	scanf ("%d", &n);
	printf ("Enter terms <coeff-i, exp-i>, in decreasing order of term exponents:\n");
	for (int i = 0; i < n; i++) {
		int e;
		float c;
		scanf ("%f %d", &c, &e);
		if (c)
			attach (c, e);
	}
	A -> finish = terms_avail - 1;
}

void display (poly A) {
	if (isZero(A)) {
		printf ("Zero Polynomial.\n");
		return;
	}
	printf ("Polynomial: ");
	for (; A.start < A.finish; A.start++)
		if (terms[A.start].coeff == 1)
			printf ("x^%d + ", terms[A.start].expo);
		else
			printf ("%.3fx^%d + ", terms[A.start].coeff, terms[A.start].expo);
	if (terms[A.finish].expo == 0)
		printf ("%.3f\n", terms[A.finish].coeff);
	else
		printf("%.3fx^%d\n", terms[A.finish].coeff, terms[A.finish].expo);
}