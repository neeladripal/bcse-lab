#include<stdio.h>
#include<stdlib.h>

typedef long long ll;

// function to return a square matrix of size n
ll** getMatrix (ll n) {
    
    // defining a matrix to take input
    ll** A = (ll**) malloc (n * (sizeof (ll*)));
    
    for(ll i = 0; i < n; i++)
        *(A + i) = (ll*) malloc (n * sizeof (ll));

    for(ll i = 0; i < n; i++)  {
        printf ("Enter elements of row %lld : ", i);
        for (ll j = 0; j < n; j++)
            scanf ("%lld", &A[i][j]);
    }   
    return A;
}

// function to apply filter
void applyFilter (ll** A, ll n, ll** filter, ll n1, ll cx, ll cy) {
    
    // check if the filter can be applied or not
    ll** temp = (ll**) malloc (n1 * sizeof(ll*));
    for (ll i = 0; i < n1; i++)
        *(temp + i) = (ll*) malloc (n1 * sizeof(ll));

    // check the boundary values
    if(cx >= n1/2 && cx < (n - n1/2) && cy >= n1/2 && cy < (n - n1/2)) {
        
        for(ll i = cx - n1/2; i <= cx + n1/2; i++) {
            for(ll j = 0; j < n1; j++) {
                ll sum = 0, k1 = 0;
                for(ll k = cy - n1/2; k <= cy + n1/2; k++) {
                    sum += A[i][k] * filter[k1][j];
                    k1++;
                }
                temp[i - cx + n1/2][j] = sum;        
            }
        }

        for(ll i = cx - n1/2; i <= cx + n1/2; i++) {
            for(ll j = cy - n1 / 2; j <= cy + n1/2; j++) {
                A[i][j] = temp[i - cx + n1/2][j - cy + n1/2];
            }
        }
    }
}

// function to print the matrix
void printMatrix (ll** A, ll n) {
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++)
            printf("%12lld ", A[i][j]);
        printf("\n");
    }
}

// function to free the space occupied by the matrix
void clearMatrix (ll* *X, ll n) {
    for (ll i = 0; i < n; i++)
        free (*(X + i));
    free (X);
}

// driver code to test the functionalities
int main () {
    ll n = 5, n1 = 3;
    printf("\nEnter the Base Matrix (5x5) --> \n");
    ll** A = getMatrix(n); // initial matrix, to be scaled upto 128 * 128

    printf("\nEnter the filter matrix (3x3) --> \n");
    ll** filter1 = getMatrix(n1); // filter matrix

    

    // apply filter for every possible positions
    for(ll cx = 0; cx < n; cx++) {
        for(ll cy = 0; cy < n; cy++) {
            applyFilter(A, n, filter1, n1, cx, cy);
        }
    }

    // print the matrix after applying filter
    printf("\nModified Matrix --> \n");
    printMatrix(A, n);

    // clear the memory occupied by the matrix
    clearMatrix (A, n);
    clearMatrix (filter1, n1);

    return 0;
}