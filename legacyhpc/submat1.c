#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	int a[5][7];				// full matrix
	MPI_Comm comm;
	int np, iam, i, j;
	MPI_Datatype submat1, submat2;
	MPI_Status sts;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);
	
	if(iam == 0)
		for(i = 0; i < 5; i++)
			for(j = 0; j < 7; j++)
				a[i][j] = i + j;
	
	MPI_Type_vector(2, 3, 7, MPI_INT, &submat1);
	MPI_Type_commit(&submat1);
	
	if(iam == 0)
		MPI_Send(&a[0][0], 1, submat1, 1, 0, comm);
	if(iam == 1)
		MPI_Recv(&a[0][0], 1, submat1, 0, 0, comm, &sts);
	
	MPI_Type_free(&submat1);
		
	if(iam == 1)
		printf("iam == 1, a[1][2] = %d\n", a[1][2]);
	
	return 0;
}
