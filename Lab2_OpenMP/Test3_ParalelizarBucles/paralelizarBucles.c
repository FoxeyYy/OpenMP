#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
/* 1. Include de biblioteca OpenMP */

#define SIZE	200000000
int main() {

	omp_set_num_threads(1);

	int *v = (int *)malloc( SIZE * sizeof(int) );
	int i;
	int suma = 0;
	double tParalelo, tTotal;
	tTotal = omp_get_wtime();

	/* Inicializar */
	tParalelo = omp_get_wtime();
	#pragma omp parallel shared(v) private(i) 
	{
	#pragma omp for
	for ( i=0; i<SIZE; i++ ) v[i] = 0;

	#pragma omp for
	/* 2. Directiva de bucle paralelo: Con vector v compartido e �ndice i privado */
	for ( i=0; i<SIZE; i++ ) v[i] = i;
	}
	tParalelo = omp_get_wtime() - tParalelo;

	/* Suma secuencial */
	for ( i=0; i<SIZE; i++ ) suma = ( suma + v[i] ) % 65535;
	tTotal = omp_get_wtime() - tTotal;
	printf( "Resultado final: %d\n Total: %lf Par: %lf\n", suma, tTotal, tParalelo );

	return 0;
}
