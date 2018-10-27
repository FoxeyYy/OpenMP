// Héctor Del Campo Pando

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define SIZE	512
#define SEED	6834723

int main() {
	int i,j;

	omp_set_num_threads(4);

	int A[ SIZE ][ SIZE ];

	srand( SEED );

	for (i=0; i<SIZE; i++) {
		A[0][i] = rand() % 10;
	    A[i][0] = rand() % 10;
	}

	for (i=1; i<SIZE; i++)
		for (j=1; j<SIZE; j++) 
			A[i][j] = A[i-1][j] + A[i][j-1];

	/* Comprobaci�n de resultados */
	int checksum = 0.0;
	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++)
			checksum += A[i][j];

	printf("Checksum: %d\n", checksum );

	return 0;
}
