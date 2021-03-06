
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define SIZE	512
#define SEED	6834723

int main() {
	int i,j,k;

	omp_set_num_threads(4);

	double A[ SIZE ][ SIZE ];
	double B[ SIZE ][ SIZE ];
	double C[ SIZE ][ SIZE ];
	double D[ SIZE ][ SIZE ];

	srand48( SEED );

	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++) {
			C[i][j] = 0;
			D[i][j] = 0;
			A[i][j] = drand48();
			B[i][j] = drand48();
		}

	/* Paralelizar esta versi�n de cada una de las 6 posibles formas */
	for (i=0; i<SIZE; i++)
			for (j=0; j<SIZE; j++) 
					#pragma omp parallel for shared(A, B, C, i, j) private( k)

					for (k=0; k<SIZE; k++) 
				#pragma omp atomic
				C[i][j] = C[i][j] + A[i][k] * B[k][j];

	/* Versi�n secuencial para comprobar resultados */
	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++) 
			for (k=0; k<SIZE; k=k+1) 
				D[i][j] = D[i][j] + A[i][k] * B[k][j];

	/* Comprobaci�n de resultados */
	int correcto = 1;
	for (i=0; i<SIZE && correcto; i++)
		for (j=0; j<SIZE && correcto; j++) 
			if ( C[i][j] != D[i][j] ) correcto = 0;

	printf("Resultado: ");
	if ( correcto )
		printf("OK\n");
	else
		printf("ERROR!!\n");
	return 0;
}
