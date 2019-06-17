bcast.c                                                                                             0000666 0001750 0001750 00000000737 13460532025 012167  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int m, n, mm[10];
	int next, front;
	MPI_Status st;

	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);
	MPI_Datatype tmptype, newtp;
	
	if(iam ==0) m =111;
	else m = 0;
	MPI_Bcast (&m, 1, MPI_INT, 1 , comm);

	printf("\n Value in proc%d is %d!\n", iam, m);

	MPI_Finalize();

	return 0;
}
                                 datatype.c                                                                                          0000666 0001750 0001750 00000001654 13460531460 012707  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int m, n;
	int next, front;
	MPI_Status st;

	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);
	MPI_Datatype tmptype, newtp;

	int blklen[2];
	MPI_Aint dspls[2];		// displacement
	MPI_Datatype dttps[2];		// datatypes

	MPI_Type_vector( m, n, lda, MPI_FLOAT, &tmptype);
	
	float a[100][111], b[70][70];
	m = 31; n =37; lda = 111;

	blklen[0] = 1;
	blklen[1] = 1;
	dspls[0] = 0;
	dspls[1] = (m * lda + n) * sizeof(float);
	dttps[0] = tmptype;
	dttps[1] = MPI_UB;

	MPI_Type_struct(2, blklen, dspls, dttps, newtp);
	MPI_Type_commit(newtp);

	if (iam == 0)
	{

	}
	else
	{


	}

		MPI_Send(&a[0][0], 1, newtp, next, 1, comm);
		MPI_Recv(&n, 1, MPI_INT, front, 1, comm, &st);
	printf("\nGet value from %d is %d!", iam, n);

	MPI_Finalize();

	return 0;
}
                                                                                    example.c                                                                                           0000666 0001750 0001750 00000000737 13447333776 012547  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	// Print out hello world in each process
	MPI_Comm comm;
	int np, iam;

	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);
	
	// main body
	printf("\nHello world from %d!", iam);
	
	// Terminate
	MPI_Finalize();
	
	return 0;
}
// Build the common lines to a library to avoid compiling these stuff everytime u need them!
                                 example1.c                                                                                          0000666 0001750 0001750 00000000552 13447356052 012613  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include "myhead.h"

int main(int argc, char **argv)
{
	// Print out hello world in each process
	int np, iam;
	MPI_Comm comm;
	
	mybegin(&argc, &argv, &comm, &np, &iam);	
	
	// main body
	printf("\nHello world from %d!", iam);
	
	// Terminate
	myend();
	
	return 0;
}
// Build the common lines to a library to avoid compiling these stuff everytime u need them!
                                                                                                                                                      gather.c                                                                                            0000666 0001750 0001750 00000001143 13460532530 012336  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int m, n, mm[10];
	int next, front;
	MPI_Status st;

	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);
	MPI_Datatype tmptype, newtp;
	
	if(iam ==0) m =111;
	else m = 0;
	
	/*MPI_Bcast (&m, 1, MPI_INT, 1 , comm);
	
	printf("\n Value in proc%d is %d!\n", iam, m);*/

	MPI_Gather(&m, 1, MPI_INT, mm, 1, MPI_INT, \
			0, comm);

	printf("\n Value in proc%d is %d, %d!\n", iam, mm[0], mm[1]);
	
	MPI_Finalize();

	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                             main.c                                                                                              0000666 0001750 0001750 00000000554 13445107320 012013  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include "myhead.h"

void main()
{
	float a[111][123], b[134][131], c[73][84];
	
	int i, j;
	int m = 11, n = 7;

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		{
			a[i][j] = i + j;
			b[i][j] = i + j;
		}

	matradd(m, n, &a[0][0], 123, &b[0][0], 131, &c[0][0], 84);

	printf("\nThe values are: %f, %f, %f\n", \
			c[0][0], c[10][1], c[7][5]);

	return 0;
}
                                                                                                                                                    matradd.c                                                                                           0000666 0001750 0001750 00000000500 13445106005 012471  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include "myhead.h"

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
                                                                                                                                                                                                mybegin.c                                                                                           0000666 0001750 0001750 00000000337 13447356102 012526  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include "myhead.h"

void mybegin(int *argc, char ***argv, MPI_Comm *comm, int *np, int *iam)
{
	MPI_Init(argc, argv);
	MPI_Comm_dup(MPI_COMM_WORLD, comm);
	MPI_Comm_size(*comm, np);
	MPI_Comm_rank(*comm, iam);

	return;
}
                                                                                                                                                                                                                                                                                                 myend.c                                                                                             0000666 0001750 0001750 00000000120 13447356111 012176  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include "myhead.h"

void myend()
{
	// Terminate
	MPI_Finalize();
	
	return;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                ring.c                                                                                              0000666 0001750 0001750 00000001213 13447342613 012027  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int m, n;
	int next, front;
	MPI_Status st;

	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);

	m = iam * 5;

	next = (iam + 1) % np;
	front = (iam - 1 + np) % np;
	if(iam == 0)
	{
		MPI_Send(&m, 1, MPI_INT, next, 1, comm);
		MPI_Recv(&n, 1, MPI_INT, front, 1, comm, &st);
	}
	else
	{
		MPI_Recv(&n, 1, MPI_INT, front, 1, comm, &st);
		MPI_Send(&m, 1, MPI_INT, next, 1, comm);
	}

	printf("\nGet value from %d is %d!", iam, n);

	MPI_Finalize();

	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                     ring1.c                                                                                             0000666 0001750 0001750 00000001217 13447343452 012116  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int m, n;
	int next, front;
	MPI_Status st;

	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);

	m = iam * 5;

	next = (iam + 1) % np;
	front = (iam - 1 + np) % np;
	if(iam % 2 == 0)
	{
		MPI_Send(&m, 1, MPI_INT, next, 1, comm);
		MPI_Recv(&n, 1, MPI_INT, front, 1, comm, &st);
	}
	else
	{
		MPI_Recv(&n, 1, MPI_INT, front, 1, comm, &st);
		MPI_Send(&m, 1, MPI_INT, next, 1, comm);
	}

	printf("\nGet value from %d is %d!", iam, n);

	MPI_Finalize();

	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                 ring2.c                                                                                             0000666 0001750 0001750 00000001347 13447347360 012125  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int m, n;
	int next, front;
	MPI_Status st;

	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);

	m = iam * 5;

	next = (iam + 1) % np;
	front = (iam - 1 + np) % np;
	/*if(iam % 2 == 0)
	{
		MPI_Send(&m, 1, MPI_INT, next, 1, comm);
		MPI_Recv(&n, 1, MPI_INT, front, 1, comm, &st);
	}
	else
	{
		MPI_Recv(&n, 1, MPI_INT, front, 1, comm, &st);
		MPI_Send(&m, 1, MPI_INT, next, 1, comm);
	}*/

	MPI_Sendrecv (&m, 1, MPI_INT, next, 1, &n, 1, MPI_INT, \
			front, 1, comm, &st);

	printf("\nGet value from %d is %d!", iam, n);

	MPI_Finalize();

	return 0;
}
                                                                                                                                                                                                                                                                                         ring3.c                                                                                             0000666 0001750 0001750 00000001623 13454033631 012112  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int m, n;
	int next, front;
	MPI_Status stas[6];
	MPI_Request reqs[6];

	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);

	m = iam * 5;

	next = (iam + 1) % np;
	front = (iam - 1 + np) % np;
	/*if(iam % 2 == 0)
	{
		MPI_Send(&m, 1, MPI_INT, next, 1, comm);
		MPI_Recv(&n, 1, MPI_INT, front, 1, comm, &st);
	}
	else
	{
		MPI_Recv(&n, 1, MPI_INT, front, 1, comm, &st);
		MPI_Send(&m, 1, MPI_INT, next, 1, comm);
	}*/

	/*MPI_Sendrecv (&m, 1, MPI_INT, next, 1, &n, 1, MPI_INT, \
			front, 1, comm, &st);*/
	
	MPI_Isend( &m, 1, MPI_INT, next, 1, comm, &reqs[0]);
	MPI_Irecv( &n, 1, MPI_INT, front, 1, comm, &reqs[1]);
	MPI_Waitall(2, reqs, stas);


	printf("\nGet value from %d is %d!", iam, n);

	MPI_Finalize();

	return 0;
}
                                                                                                             test.c                                                                                              0000666 0001750 0001750 00000000444 13456502702 012051  0                                                                                                    ustar   lengran                         lengran                                                                                                                                                                                                                #include <iostream>

using namespace std;

int CompareInt (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

int main()
{
	int a[] = {1, 4, 6, 2, 99, 234, 0};
	qsort(a, 7, sizeof(int), CompareInt);

	for (int i = 0; i < 7; i++)
	{
		printf("%d ", a[i]);
	}
	
	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            