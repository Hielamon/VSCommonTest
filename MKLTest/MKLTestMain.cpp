#include <stdio.h>  
#include <malloc.h>  
#include <mkl_blas.h>  
#include <mkl_cblas.h>  

#define N   100  
void initVector(float* v)
{
	for (int i = 0; i < N; i++)
		v[i] = -i*1.0f;
}

int main(int argc, char* argv[])
{
	float* vector = (float*)malloc(sizeof(float)*N);
	initVector(vector);

	int a1 = N;
	int incx1 = 1;
	float ret1 = sasum(&a1, vector, &incx1);    // FORTRAN 77接口形式  
	printf("Result of sasum: %lf\n", ret1);

	int a2 = N / 2;
	int incx2 = 2;
	float ret2 = sasum(&a2, vector, &incx2);    // FORTRAN 77接口形式  
	printf("Result of sasum: %lf\n", ret2);

	float ret3 = cblas_sasum(N, vector, 1);     //C接口形式  
	printf("Result of sasum: %lf\n", ret3);

	free(vector);

	return 0;
}