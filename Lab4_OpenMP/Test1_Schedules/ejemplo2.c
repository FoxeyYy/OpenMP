
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define SIZE	768
#define SEED	6834723

int main() {
	int i,j,k;
	omp_set_num_threads(4);

	double V[ SIZE ][ SIZE ];

	srand48( SEED );

	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++) {
			V[i][j] = drand48();
		}

	/* Paralelizar esta parte del c�digo */
	#pragma omp parallel for shared(V) private(i,j) schedule(dynamic, 16)
	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++) {
			int end = 0;
			while ( !end ) {
				V[i][j] += 0.00001 + 0.0002 * (double)i/SIZE * (double)j/SIZE;
				if ( V[i][j] > 1.0 ) end = 1;
			}
		}

	/* Comprobaci�n de resultados */
	double checksum = 0.0;
	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++) {
			checksum = checksum + V[i][j] - 1;
		}

	printf("Resultado: %.10lf\n", checksum);
	return 0;
}
