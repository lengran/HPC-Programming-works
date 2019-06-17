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
	
	int blk[2];
	MPI_Aint dsp[2];
	MPI_Datatype typs[2];
	
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
	
	blk[0] = 1;
	blk[1] = 1;
	dsp[0] = 0;
	dsp[1] = (2 * 7 + 3) * sizeof(int);
	typs[0] = submat1;
	typs[1] = MPI_UB;
	MPI_Type_struct(2, blk, dsp, typs, &submat2);
	MPI_Type_commit(&submat2);
	
	if(iam == 0)
		MPI_Send(&a[0][0], 2, submat2, 1, 0, comm);
	if(iam == 1)
		MPI_Recv(&a[0][0], 2, submat2, 0, 0, comm, &sts);

	MPI_Type_free(&submat1);
	MPI_Type_free(&submat2);
	
	if(iam == 1)
		printf("a[1][2] = %d\na[1][3] = %d\na[2][3] = %d\na[3][5] = %d\n", a[1][2], a[1][3], a[2][3], a[3][5]);
	
	return 0;
}
