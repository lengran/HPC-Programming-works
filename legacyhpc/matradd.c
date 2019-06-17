#include "myhead.h"

void matradd( m, n, a, lda, b, ldb, c, ldc)
int m, n, lda, ldb, ldc;
float *a, *b, *c;
{
	int i, j;
	
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)						// C和Fortran的按行列存储相反
			c[i * ldc + j] = a[i * lda + j] + b[i * ldb + j];	// 把二维数组当成一维处理

	return;
}
