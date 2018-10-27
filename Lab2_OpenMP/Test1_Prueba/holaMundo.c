#include<stdio.h>
#include<omp.h>
/* 1. Include de biblioteca OpenMP */

int main() {

	omp_set_num_threads(8);

	/* 2. Directiva de paralelismo */
	#pragma omp parallel
	/* 3. Escribir el identificador de thread y la cantidad de threads */
	printf("Hola mundo desde %d de %d\n", omp_get_thread_num(), omp_get_num_threads());

	return 0;
}
