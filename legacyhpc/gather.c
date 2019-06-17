#include <stdlib.h>
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
	
	if(iam == 0) m = 111;
	else m = iam;
	
	/*MPI_Bcast (&m, 1, MPI_INT, 1 , comm);
	
	printf("\n Value in proc%d is %d!\n", iam, m);*/
	
	int root = 1;

	MPI_Gather(&m, 1, MPI_INT, mm, 1, MPI_INT, \
			root, comm);
	if(iam == root)
	printf("\n Value in proc%d is %d, %d, %d!\n", iam, mm[0], mm[1], mm[2]);
	
	MPI_Finalize();

	return 0;
}
