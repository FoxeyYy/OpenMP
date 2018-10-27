#include<stdio.h>
#include<omp.h>
/* 1. Include de biblioteca OpenMP */

int main() {

	int v[ 10 ];
	int i;
	omp_set_num_threads(40);

	/* Inicializar */
	for ( i=0; i<10; i++ ) v[i] = 0;

	/* 2. Directiva de paralelismo: Con vector v compartido */
	#pragma omp parallel shared(v)
	/* 3. Dentro de la regi�n paralela: Cada thread escribe la posici�n
	 * 		de su identificador un 10 + su identificador */
	{
		v[ omp_get_thread_num() ] = 10 + omp_get_thread_num();
	}
	/* etc ... (Reescribir en paralelo) */

	/* Escribir */
	for ( i=0; i<10; i++ ) printf( " %d", v[i] );
	printf( "\n" );

	return 0;
}
