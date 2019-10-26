#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "mkl_lapacke.h"

// Generate random matrix
double *generate_matrix(int size)
{
    int i;
    double *matrix = (double *)malloc(sizeof(double) * size * size);
    srand(1);

    for (i = 0; i < size * size; i++)
    {
        matrix[i] = rand() % 100;
    }

    return matrix;
}

// Display matrix
void print_matrix(const char *name, double *matrix, int size)
{
    int i, j;
    printf("\n");
    printf("matrix: %s \n", name);

    for (i = 0; i < size; i++)
    {
            for (j = 0; j < size; j++)
            {
                printf("%5.3f ", matrix[i * size + j]);
            }
            printf("\n");
    }
}

// Check result
int check_result(double *bref, double *b, int size) {
    int i;
    for(i=0;i<size*size;i++) {
        if (abs(bref[i]!=b[i]) !=0) return 0;
    }
    return 1;
}


// Qr decomposition
void QR(double *A, int n, double* q, double* r) {
    int i,j,k; // Loop variables
    double SD; // Stockage double

    // Init r and q
    for (i=0;i<n*n;i++) {
        r[i] = 0;
        q[i] = 0;
    }

    // Main to have Q an orthogonal matrix and R an upper triangular matrix
    for (k=0;k<n;k++){
        SD=0;
        for (j=0;j<n;j++) {
            SD += pow(A[j*n+k], 2);
        }
        r[k*n+k] = sqrt(SD);
        for (j=0;j<n;j++) {
            q[j*n+k] = A[j*n+k]/r[k*n+k];
        }
        for (i=k;i<n;i++) {
            SD=0;
            for (j=0;j<n;j++){
                SD += A[j*n+i] * q[j*n+k];
            }
            r[k*n+i] = SD;
            for (j=0;j<n;j++){
                A[j*n+i] -= r[k*n+i]*q[j*n+k];
            }
        }
    }
} 


// Returns the transposition of the given matrix into a parameter
double* Transposed(int n, double* Mat){
    int i, j; // Loop variables
    double* T = (double *)malloc(sizeof(double) * n * n); // Transposed matrix

    // Loop
    for (i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            // We transpose each element of our parameter matrix into our transposed matrix
            T[i*n+j]=Mat[j*n+i];
        }
    }
    // We return the transposed matrix
    return T;	
}

// Computation between two matrices
double* ProdMat(int n, double* Mat1, double* Mat2)
{
    int i,j,k; // Loop variables
    double sum;
    double* res = (double *)malloc(sizeof(double) * n * n); // Result matrix

    // Calculate product
    for (i = 0; i < n; i++) {
        for (j = 0; j<n ; j++) {
            sum = 0.0;
            for(k=0; k<n ; k++) {
                sum += Mat1[i*n+k]*Mat2[k*n+j];
            }
            res[i*n+j] = sum;
        }
    }

    // We return the final product
    return res;
}

// Reverse a matrix by resolving a system
double* ReverseSys(double* mat, int n) {
    int i,j,k,l,m; // Loop variables
    double* stock = (double *)malloc(sizeof(double) * n * n); // Storage matrix that will play the "role" of the identity matrix
    double* rev= (double *)malloc(sizeof(double) * n * n); // Reverse matrix to display

    for(i=0;i<n*n;i++) {
        // We put zeros in the storage matrix
        stock[i]=0;
        // We assign to our inverse matrix the values of our given matrix as parameters
        rev[i]=mat[i];
    }

    // The operations are only carried out on the storage matrix, so we go through this matrix
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            // The pivot is chosen as part of the diagonal
            stock[i*n+i]=1/rev[i*n+i];
            // If we are not in the diagonal 
            if(j!=i) {
                // We divide the elements of our line by our pivot
                stock[i*n+j]=-rev[i*n+j]/rev[i*n+i];
            }
            for(k=0; k<n; k++) {
                // Diagonal
                if(k!=i) {
                    // Dilatation
                    stock[k*n+i]=rev[k*n+i]/rev[i*n+i];
                }
                // Outside the diagonal 
                if(j!=i && k!=i) {
                    // Transvection composed of the previous computation 
                    stock[k*n+j]=rev[k*n+j]-rev[i*n+j]*rev[k*n+i]/rev[i*n+i];
                }
            }
        }
        // Our reversed matrix is assigned the values from our storage matrix (which therefore correspond to the reversed values).
        for(l=0; l<n; l++) {
            for(m=0; m<n; m++) {
                rev[l*n+m]=stock[l*n+m];
            }
        }
    }
    // The space allocated for the storage matrix is freed up
    free(stock);

    // We return the reversed matrix
    return rev;
}

double* my_dgesv(int n, double *a, double *b) {

    // Creation of Q and R
    double* Q = (double *)malloc(sizeof(double) * (n) * (n));
    double* R = (double *)malloc(sizeof(double) * (n) * (n));

    // Using the QR algorithm
    QR(a,n, Q, R);
    // Display
    //print_matrix("Q", Q, n);
    //print_matrix("R", R, n);

    /*
        To solve the AX=B system, we now have: QRX = Y or RX = Q^T*Y.
        The system can therefore be solved quickly with the last formula.
    */

    // Q transposed
    double *Qtrans;
    Qtrans = Transposed(n, Q);

    // Reverse of R
    double* Rinv;
    Rinv = ReverseSys(R,n);

    // Find X : X = R^-1*Q^T*Y.
    double* x;
    double* res1;
    res1 = ProdMat(n, Qtrans, b);
    x = ProdMat(n,Rinv,res1);

    // We free up the space allocated by the matrices
    free(R);
    free(Q);
    free(Qtrans);
    free(Rinv);
    free(res1);

    // We return our solution
    return x;
}

    int main(int argc, char *argv[])
    {

        // Size given by the user
        int size = atoi(argv[1]);

        // Init
        double *a; // *aref;
        double *b; // *bref;

        // Creation of A
        a = generate_matrix(size);
        //aref = generate_matrix(size);
        //print_matrix("A", a, size);

        // Creation of B
        b = generate_matrix(size);
        //bref = generate_matrix(size);
        //print_matrix("B", b, size);

        // Using MKL to solve the system
        //MKL_INT n = size, nrhs = size, lda = size, ldb = size, info;
        //MKL_INT *ipiv = (MKL_INT *)malloc(sizeof(MKL_INT)*size);

        clock_t tStart = clock();
        //info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, aref, lda, ipiv, bref, ldb);
        //printf("Time taken by MKL: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

        //tStart = clock();
        double* X;
        X = my_dgesv(size, a, b);
        printf("Time taken by my implementation: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
        
        //if (check_result(bref,X,size)==1)
        //    printf("Result is ok!\n");
        //else    
        //    printf("Result is wrong!\n");
        
        //print_matrix("X", X, size);
        //print_matrix("Xref", bref, size);

        // We free up the space allocated by the matrices
        free(a);
        free(b);
        //free(aref);
        //free(bref);
        free(X);
        return 0;
    }
