#include <stdlib.h>
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
