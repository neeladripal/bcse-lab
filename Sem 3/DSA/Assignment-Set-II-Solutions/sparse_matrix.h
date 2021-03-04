#define MAX_TERMS 101
// defining the structure for each term in a sparse matrix
typedef struct {
	int row, col, value;
} sparse;

int isNonZero (sparse *s) {		// checks if a matrix is null matrix
	return s[0].value > 0;
}

int compare (sparse A, sparse B, int col) { 	// compare positions of two terms to store in row major order
	if (A.row * col + A.col > B.row * col + B.col)
		return 1;
	else if (A.row * col + A.col == B.row * col + B.col)
		return 0;
	else
		return -1;
}

// function to take input in a sparse matrix
void getMatrix (sparse* s) {
	printf ("Enter number of rows: ");
	scanf ("%d", &s[0].row);

	printf ("Enter number of colmuns: ");
	scanf ("%d", &s[0].col);

	printf ("Enter the number of non zero terms: ");
	scanf ("%d", &s[0].value);

	if (s[0].value > s[0].row * s[0].col) {
		printf ("Number of terms exceeds capacity of matrix.\n");
		return;
	}

	// get the other elements of the matrix
	if (isNonZero(s)) {
		printf("Enter the values in row-major order in <row_no, col_no, value> format -->\n");
		for (int i = 1; i <= s[0].value; i++)
			scanf("%d %d %d", &s[i].row, &s[i].col, &s[i].value);
	}
}

// function to display the sparse matrix
void displayMatrix(sparse* s) {
	printf ("Resultant Sparse Matrix -->\n");

	if (isNonZero(s)) {
		
		// display the number of rows and columns
		printf ("Number of rows: %d      Number of columns: %d\n", s[0].row, s[0].col);
		printf ("Row    Column Value \n");
		
		// display the rest of the items
		for (int i = 1; i <= s[0].value; i++) {
			printf("%6d %6d %6d\n", s[i].row, s[i].col, s[i].value);
		}
	}
	else
		printf ("Zero Matrix.\n");
}

// function to transpose the sparse matrix
void transpose (sparse* A, sparse* B) {
	int *rowTerms = (int *) malloc ((A[0].col) * sizeof (int)), *startPos = (int *) malloc ((A[0].col) * sizeof (int));

	// interchange number of row and columns
	B[0].row = A[0].col;
	B[0].col = A[0].row;

	B[0].value = A[0].value; // keep number of terms same

	if (isNonZero(A)) { //check for zero matrix
		// initialise the number of non-zero terms in each column with zero
		for (int i = 0; i < A[0].col; i++)
			rowTerms[i] = 0;

		// count the number of row terms in each column
		for (int i = 1; i <= A[0].value; i++) {
			rowTerms[A[i].col]++;
		}

		// determine the starting position of each column as row in transposed matrix
		startPos[0] = 1;
		for (int i = 1; i < A[0].col; i++)
			startPos[i] = startPos[i - 1] + rowTerms[i - 1];

		// perform the transpose operation
		for (int i = 1; i <= A[0].value; i++) {

			int j = startPos[A[i].col]++; // incrementing the starting position to give the next postion for the corresponding column

			// adding a term to the transposed matrix
			B[j].row = A[i].col;
			B[j].col = A[i].row;
			B[j].value = A[i].value;
		}
	}

	free (rowTerms);
	free (startPos);
}

void storeSum (sparse* C, int* t, int r, int c, int v) {		// attach a term to the resultant matrix
	if (v) {	// if the value is non-zero
		
		if (*t < MAX_TERMS) {	// if no of terms doesn't exceed MAX_TERMS
			
			// add a term to the matrix and increment the index
			C[++*t].row = r;
			C[*t].col = c;
			C[*t].value = v;
		}
		else
			printf ("Number of terms exceeds %d.\n", MAX_TERMS);
	}
}

void add (sparse* A, sparse* B, sparse* C) {
	if ((A[0].row == A[0].row) && (A[0].col == B[0].col)) { // check compatibility for matrix addition
		
		C[0].row =A[0].row;			// number of rows in resultant matrix is equal to that of each child matrix
		C[0].col =A[0].col;			// number of columns in resultant matrix is equal to that of each child matrix
		
		int i = 1, j = 1, totalC = 0;
		while (i <= A[0].value && j <= B[0].value)
			switch (compare(A[i], B[j], C[0].col)) {
				
				// if position of term of matrix A comes before
				case -1: storeSum (C, &totalC, A[i].row, A[i].col, A[i].value);
						i++;
						break;
				
				// if position of both terms are equal
				case 0: storeSum (C, &totalC, A[i].row, A[i].col, A[i].value + B[j].value);
						i++; j++;
						break;
				
				// if position of term of matrix B comes before
				case 1: storeSum (C, &totalC, B[j].row, B[j].col, B[j].value);
						j++;
						break;
			}
		
		// attach the residual terms (if any)
		for (; i <= A[0].value; i++)
		storeSum (C, &totalC, A[i].row, A[i].col, A[i].value);
		for (; j <= B[0].value; j++)
		storeSum (C, &totalC, B[j].row, B[j].col, B[j].value);
		
		C[0].value = totalC;
	}
	else // non compatible matrices
		printf("Inompatible Matrices !\n");
}

void mult (sparse* A, sparse* B, sparse* C) {
	if (A[0].col != B[0].row) { 		//condition for incompatibility for matrix multiplication
		printf("Incompatible matrices !\n");
		return;
	}

	sparse newB[MAX_TERMS];
	transpose (B, newB);	// take transpose of B and store in newB
	
	int totalC = 0, rowBegin = 1, row = A[1].row, column, sum = 0;
	
	// set up the boundary conditions
	A[A[0].value + 1].row = A[0].row;
	newB[B[0].value + 1].col = B[0].col;

	for (int i = 1; i <= A[0].value;) {
		column = newB[1].row;

		for (int j = 1; j <= B[0].value + 1;) {
			// multiply row of A by column of B
			if (A[i].row != row) {		// if no more non-zero term left in previous row of A
				storeSum (C, &totalC, row, column, sum);	// store the sum as a new term in C
				sum = 0;
				i = rowBegin;	// set i to first term of the previous row of A
				for (; newB[j].row == column; j++);
				column = newB[j].row;	// set column to next column of B
			}

			else if (newB[j].row != column) {	// if no more non-zero term left in previous column of B
				storeSum (C, &totalC, row, column, sum);	// store the sum as a new term in C
				sum = 0;
				i = rowBegin;	// set i to first term of the current row of A
				column = newB[j].row;	// set column to current column of B
			}

			else {		// compare terms in a particular row of A and column of B
				if (A[i].col < newB[j].col)
					i++;	// go to next term in A
				else if (A[i].col == newB[j].col)
					sum += (A[i++].value * newB[j++].value);	// add terms, go to nexct term in A and B
				else
					j++;	// got to next term in B
			}
		}

		for (; A[i].row == row; i++);	// advance to next row in A
		rowBegin = i;
		row = A[i].row;
	}

	// update the values for dimensions and no of terms in C
	C[0].row = A[0].row;
	C[0].col = B[0].col;
	C[0].value = totalC;
}