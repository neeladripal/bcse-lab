/* A polynomial is represented by the start and finish indices in a terms array where the terms of the poynomial are stored. */
#define MAX_TERMS 1000

// structure for coefficient and exponent of a single polynomial
typedef struct {
	float coeff;
	int expo;
} polterm;

polterm terms[MAX_TERMS];		// a single array containing terms of all polynomials
int terms_avail = 0;				// index of next available slot in terms array to store a polynomial

// straucture to store the start and end index of a polynomial in the terms array
typedef struct {
	int start;
	int finish;
} poly;

// function to compare two terms based on their exponents
int compare (const void *X, const void *Y) {
	int a = ((polterm*)X) -> expo, b = ((polterm*)Y) -> expo;
	if (a > b)
		return -1;
	else if (a < b)
		return 1;
	else
		return 0;
}

// function to check if a polynomial is zero polynomial
int isZero (poly A) {
	return (A.finish < A.start);		// finish index = start index - 1 for zero polynomial
}

// function to return the coefficient of a particular term (identified by its exponent) in a polynomial
float coef (poly A, int e) {
	for (int i = A.start; i <= A.finish; i++) {
		if (terms[i].expo == e)			// iterate over the terms and look if a term with the given exponent exists
			return terms[i].coeff;
	}
	return 0;							// 0, if there is no such term
}

// function to compute degree of a polynomial
int degree (poly A) {
	if (isZero(A))
		return -1;						// if zero, return an invalid value
	else
		return terms[A.start].expo;		// else, return highest exponent
}

// function to append a new polynomial term to the terms array
void attach (poly* X, float c, int e) {
	if (c) {
		if (terms_avail >= MAX_TERMS) {
			printf ("Too many terms in the polynomial.\n");
			exit (0);
		}
		terms[terms_avail].coeff = c;
		terms[terms_avail++].expo = e;			// increment the terms_avail index to indicate the next free slot
		X -> finish = terms_avail - 1;			// update the finish index of the updated polynomial
	}
}

// function to add a term to a poylnomial
void addSingleTerm (poly* X, float c, int e) {
	if (c) {
		for (int i = X -> start; i <= X -> finish; i++)
			if (terms[i].expo == e) {			// if a term with the exponent exists
				terms[i].coeff += c;			// update its coefficent
				return;
			}
		attach (X, c, e);				// else attach the term to the terms array
	}
}

// function to add two polynomials
void add (poly* X, poly A, poly B) {
	float coefficient;
	X -> start = terms_avail;				// update the start index of the resultant polynomial
	X -> finish = terms_avail - 1;			// update the finish index of the resultant polynomial
	while (A.start <= A.finish && B.start <= B.finish)
		switch(compare((const void*)(terms + A.start), (const void*)(terms + B.start))) {
			case 1:																// if exponent of next term of A > exponent of next term of B
				attach(X, terms[B.start].coeff, terms[B.start].expo);			// attach next term of B
				B.start++;
				break;
			case 0:																// if exponent of next term of A = exponent of next term of B
				coefficient = terms[A.start].coeff + terms[B.start].coeff;		// add the coefficients
				attach (X, coefficient, terms[A.start].expo);				// attach the resultant term
				A.start++;
				B.start++;
				break;
			case -1:															// if exponent of next term of A < exponent of next term of B
				attach(X, terms[A.start].coeff, terms[A.start].expo);			// attach the resultant term
				A.start++;
				break;
		}
	
	// if some terms of any polynomial are left, append them
	for (; A.start <= A.finish; A.start++)
		attach(X, terms[A.start].coeff, terms[A.start].expo);
	for (; B.start <= B.finish; B.start++)
		attach(X, terms[B.start].coeff, terms[B.start].expo);
}

// function to multiply a polynomial by a constant
void cMult (poly A, float m) {
	for (int i = A.start; i <= A.finish; i++)
		terms[i].coeff *= m;		// multiply all terms with a constant
}

// function to multiply two polynomials
void mult (poly* X, poly A, poly B) {
	X -> start = terms_avail;				// update the start index of the resultant polynomial
	X -> finish = terms_avail - 1;			// update the finish index of the resultant polynomial

	// multiply ith term of polynomial A with jth term of polynomial B
	for (int i = A.start; i <= A.finish; i++)
		for (int j = B.start; j <= B.finish; j++) {
			float coefficient = terms[i].coeff * terms[j].coeff;
			int exponent = terms[i].expo + terms[j].expo;
			addSingleTerm (X, coefficient, exponent);  	// add the term to the polynomial
		}
	if (!isZero(*X))
		qsort (terms + X -> start, X -> finish - X -> start + 1, sizeof(polterm), compare);		// sort the terms in descending order of their exponents
}

// function to input a polynomial and store it in the terms array
int input (poly* A) {
	A -> start = terms_avail;
	A -> finish = terms_avail - 1;
	int n;
	printf ("Enter number of terms: ");
	scanf ("%d", &n);
	printf ("Enter terms <coeff-i, exp-i>:\n");
	for (int i = 0; i < n; i++) {
		int e;
		float c;
		scanf ("%f %d", &c, &e);
		if (e < 0) {
			printf ("Exponent cannot be negative.");
			return 1;
		}
		attach (A, c, e);
	}
	if (!isZero(*A))
		qsort (terms + A -> start, A -> finish - A -> start + 1, sizeof(polterm), compare);		// sort the terms in decreasing order of their exponents
	return 0;
}

// function to display a polynomial
void display (poly A) {
	if (isZero(A)) {
		printf ("Zero Polynomial.\n");
		return;
	}
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