#include <stdlib.h>
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
