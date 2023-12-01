/*  Name: Kayleigh Vu
    Date: 10/12/2023
    Title: Lab4 – Step 4
    Description: This program computes the product of two matrices sized N*M and M*L to make a size N*L matrix using threads
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int N, M, L;
//A, B, C matrices
double **matrixA, **matrixB, **matrixC;

//function prototypes
void initializeMatrix(int r,int c, double **matrix); //initialize matrix with random values
void printMatrix(int r,int c, double **matrix); //print matrix
void *multiplyRow(void* arg); //thread multiply function

//read N, M, and L as command-line arguments
int main(int argc,char *argv[]) {
    int i, j;

    if (argc < 4) {
        printf("Usage: %s N M L \n", argv[0]);
        exit(0);
    }

    //set arguments given by user to the global variables
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    L = atoi(argv[3]);

    //initializing matrices A, B, C in main because it does not work in function
    //matrix A (N*M)
    matrixA = malloc(N * sizeof(double *));   //allocating space for matrix
    for (i = 0; i < N; i++){
        matrixA[i] = malloc(M * sizeof(double));
    }

    //matrix B (M*L)
    matrixB = malloc(M * sizeof(double *));   //allocating space for matrix
    for (i = 0; i < M; i++){
        matrixB[i] = malloc(L * sizeof(double));
    }

    //matrix C (N*L)
    matrixC = malloc(N * sizeof(double *));   //allocating space for matrix
    for (i = 0; i < N; i++){
        matrixC[i] = malloc(L * sizeof(double));
    }

    srand(time(NULL));
    initializeMatrix(N, M, matrixA);
    initializeMatrix(M, L, matrixB);

    printf("Matrix A:\n");
    printMatrix(N, M, matrixA);

    printf("Matrix B:\n");
    printMatrix(M, L, matrixB);

    //creating N threads, each multiplying ith row of matrixA by each column of matrixB to produce the row of matrixC
    pthread_t threads[N]; //N total threads
    for (i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, multiplyRow, (void *)(size_t) i);
    
    for (i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    printf("Matrix C:\n");
    printMatrix(N, L, matrixC);
} 

void printMatrix(int r, int c, double **matrix) {
    int i, j;

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            printf("%.1f ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void initializeMatrix(int r, int c, double **matrix) {
    int i, j;

    // matrix = malloc(r * sizeof(double *));   //allocating space for matrix
    // for (i = 0; i < r; i++){
    //     matrix[i] = malloc(c * sizeof(double));
    // }
    
    //check main for matrix initilization because seg faulting when initializing in this function

    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            matrix[i][j] = rand() % 10;     //setting random values to each slot of matrix
        }
    }
}

void *multiplyRow(void* arg) {
    size_t row_index = (size_t )arg;
    int i, j;

    for (i = 0; i < L; i++) {
        size_t matrix_temp = 0;
        for (j = 0; j < M; j++) {
            matrix_temp += matrixA[row_index][j] * matrixB[j][i];
        }
        matrixC[row_index][i] = matrix_temp;
    }
}
