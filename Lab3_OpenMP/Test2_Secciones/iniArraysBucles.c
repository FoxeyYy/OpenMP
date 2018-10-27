#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define SIZE	50000000
#define	SEED	387454

int main() {

	double *A = (double *)malloc( SIZE * sizeof(double) );
	double *B = (double *)malloc( SIZE * sizeof(double) );
	double *C = (double *)malloc( SIZE * sizeof(double) );
	int i;
	omp_set_num_threads(4);

	/* 1. Paralelizar la inicializaci�n con bucle paralelo */
#pragma omp parallel for shared(A, B, C) private(i)
	for ( i=0; i<SIZE; i++ ) {
		A[i] = i * 25 % 65536 + 33;
		B[i] = (i + SIZE) / 2 % 457 - 17;
		C[i] = 0;
	}

	/* Suma vectores */
	for (i=0; i<SIZE; i++)
		C[i] = A[i] + B[i];

	return 0;
}
