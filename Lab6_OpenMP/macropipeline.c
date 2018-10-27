// Héctor Del Campo Pando

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define SIZE	2048
#define SEED	6834723
#define TIME    SIZE*2
#define BLOCK	32
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int main() {
	int i,j,t, tj, ti;

	omp_set_num_threads(4);

	int A[ SIZE ][ SIZE ] = {{0}};

	srand( SEED );

	for (i=0; i<SIZE; i++) {
		A[0][i] = rand() % 30;
	    A[i][0] = rand() % 30;
	}

    #pragma omp parallel
	{
    #pragma omp single
    for (t=0; t<TIME; t++) {
		for (ti=0; ti<SIZE; ti += BLOCK) {
			for (tj=0; tj<SIZE; tj += BLOCK) {
				#pragma omp task private(i,j) shared(ti, tj, A) default(none) \
					depend(in: A[ti+BLOCK-1][tj-1]) depend(in: A[ti-1][tj+BLOCK-1]) \
					depend(in: A[ti+BLOCK*2-1][tj+BLOCK-1]) depend(in: A[ti+BLOCK-1][tj+BLOCK*2-1]) \
					depend(out: A[ti+BLOCK-1][tj+BLOCK-1])
				for (i=ti; i<MIN(SIZE, BLOCK+ti); i++) {
					for (j=tj; j<MIN(SIZE, BLOCK+tj); j++) {
						if (i > 0 && j == 0) {
	    					A[i][0] += 4;
						} else if (j > 0 && i == 0) {
							A[0][j] += 2;
						}

						if (0 != i && 0 != j) {
							A[i][j] = (A[i-1][j] + A[i][j-1] + A[i][j])/3;
						}
					}
				}
			}
		}
	}
	}
	
	/* Comprobaci�n de resultados */
	int checksum = 0.0;
	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++)
			checksum += A[i][j];

	printf("Checksum: %d\n", checksum );

	return 0;
}
