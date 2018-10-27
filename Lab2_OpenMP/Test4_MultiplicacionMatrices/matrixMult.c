
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define SIZE	1024
#define SEED	6834723

int main() {
	int i,j,k;

	double A[ SIZE ][ SIZE ];
	double B[ SIZE ][ SIZE ];
	double C[ SIZE ][ SIZE ];

	omp_set_num_threads(4);

	srand48( SEED );

	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++) {
			C[i][j] = 0;
			A[i][j] = drand48();
			B[i][j] = drand48();
		}

	#pragma omp parallel for shared(A,B,C) private(i,j,k)
	for (i=0; i<SIZE; i++)
		for (k=0; k<SIZE; k++) 
			for (j=0; j<SIZE; j++) 
				C[i][j] = C[i][j] + A[i][k] * B[k][j];

	printf("Fin: %lf\n", C[0][0]);
	return 0;

}
