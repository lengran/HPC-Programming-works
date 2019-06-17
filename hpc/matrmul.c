#include "myhead.h"

void transpose(float * a, int m, int n)
{
	float *tmp = (float *)malloc(m * n * sizeof(float));
	for (int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			tmp[j * m + i] = a[i * n + j];
	for (int i = 0; i < m * n; i++)
		a[i] = tmp[i];
	free(tmp);
}

// a: m x n, b: n x k, c = a * b = m x k
void matrmul(MPI_Comm comm, int np, int iam, float *a, float *b, float *c, int m, int n, int k)
{
	float *partialA = (float *)malloc((m / np * n) * sizeof(float));
	float *partialB = (float *)malloc((k / np * n) * sizeof(float));
	float *bufferPartialB = (float *)malloc((k / np * n) * sizeof(float));	// for send & recv
	float *partialC = (float *)malloc((m / np * k / np) * sizeof(float));
	float *buffer;															// process 0 only
	
	MPI_Status status;
	int next = (iam + 1) % np;
	int prev = (iam - 1 + np) % np;
	
	if (iam == 0)
	{
		buffer = (float *)malloc(np * (m /np * k / np) * sizeof(float));
		printf("Process %d: np = %d, m = %d, n = %d, k = %d\n", iam, np, m, n, k);
		//printf("Process %d: sizeof partial a = %d\n", iam, (m / np * n));
		//printf("Process %d: sizeof partial b = %d\n", iam, (k / np * n));
		//printf("Process %d: sizeof partial c = %d\n", iam, (m / np * k / np));
	}
	
	// load data
	for (int i = 0; i < (m / np); i++)
		for(int j = 0; j < n; j++)
		{
			partialA[i * n + j] = a[(m / np * iam + i) * n + j];
			//printf("Process %d: partialA[%d] = %f\n", iam, j, partialA[j]);
		}
	transpose(b, n, k);														// transpose matrix b: n*k ==> k*n
	for (int i = 0; i < (k / np); i++)
		for (int j = 0; j < n; j++)
		{
			partialB[i * n + j] = b[(k / np * iam + i) * n + j];
			//printf("Process %d: partialB[%d] = %f\n", iam, j, partialB[j]);
		}
	
	for (int step = 0; step < np; step++)
	{
		for (int i = 0; i < (m / np * k / np); i++)
			partialC[i] = 0;
		
		if (iam == 0)
			printf("Process %d: Calculation step %d.\n", iam, step);
		// Generate partial result
		for (int i = 0; i < (m / np); i++)
			for (int j = 0; j < (k / np); j++)
				for (int tmp = 0; tmp < n; tmp++)
				{
					partialC[i * m / np + j] += partialA[i * n + tmp] * partialB[j * n + tmp];
					if(iam == 0)
						printf("Process %d: tmp = %d, a = %f, b = %f, c = %f\n", iam, tmp, partialA[i * n + tmp], partialB[j * k + tmp], partialC[i * m / np + j]);
				}
		
		// Gather partial result to process 0
		MPI_Gather(partialC, (m /np * k / np), MPI_FLOAT, buffer, (m /np * k / np), MPI_FLOAT, 0, comm);
		//printf("Process %d: Results gathered.\n", iam);
		
		// c[i + process * (m / np)][j + ((process + step) % np) * (k / np)] = buffer[process][i][j];
		if (iam == 0)
			for (int process = 0; process < np; process++)
				for(int i = 0; i < (m / np); i++)
					for(int j = 0; j < (k / np); j++)
						c[(i + (process * (m / np))) * k + (j + (((process + step) % np) * (k / np)))] = buffer[process * (m / np * k / np) + i * (k / np) + j];
		
		// exchange matrix partial b
		if (iam == 0)
		{
			MPI_Send(partialB, (k / np * n), MPI_FLOAT, prev, 1, comm);
			//printf("Process %d: Partial matrix b send.\n", iam);
			MPI_Recv(bufferPartialB, (k / np * n), MPI_FLOAT, next, 1, comm, &status);
			//printf("Process %d: Partial matrix b received.\n", iam);
		}
		else
		{
			MPI_Recv(bufferPartialB, (k / np * n), MPI_FLOAT, next, 1, comm, &status);
			//printf("Process %d: Partial matrix b received.\n", iam);
			MPI_Send(partialB, (k / np * n), MPI_FLOAT, prev, 1, comm);
			//printf("Process %d: Partial matrix b send.\n", iam);
		}
		for (int i = 0; i < (k / np * n); i++)
			partialB[i] = bufferPartialB[i];
		//printf("Process %d: Exchange matrix partial B.\n", iam);
	}
}