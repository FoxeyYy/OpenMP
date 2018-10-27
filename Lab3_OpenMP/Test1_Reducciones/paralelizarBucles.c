#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
/* 1. Include de biblioteca OpenMP */

#define SIZE	200000000
int main() {

	int *v = (int *)malloc( SIZE * sizeof(int) );
	int i;
	int suma = 0;
	omp_set_num_threads(4);

	/* 1. Paralelizar la inicializaci�n */
	for ( i=0; i<SIZE; i++ ) v[i] = i;

	/* 2. Paralelizar la suma, utilizando la cl�usula de reducci�n */
	#pragma omp parallel for shared(v) reduction(+:suma)
	for ( i=0; i<SIZE; i++ ) { 
		suma = ( suma  + v[i] )  % 65535;
	}

	suma = suma % 65535;
	
	printf( "Resultado final: %d\n", suma );

	return 0;
}
