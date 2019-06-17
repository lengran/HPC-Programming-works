#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void begin(int *argc, char ***argv, MPI_Comm *comm, int *np, int *iam)
{
	MPI_Init(argc, argv);
	MPI_Comm_dup(MPI_COMM_WORLD, comm);
	MPI_Comm_size(*comm, np);
	MPI_Comm_rank(*comm, iam);
}

void end()
{
	MPI_Finalize();
}

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int m, n, mm[20], dspls[11], rcs[11], lda, root, i, j, res[20];
	//MPI_Comm rowcomm, colcomm;
	//float a[100][111], b[11][13], c[11][17], w[13][17];
	//MPI_Datatype newtp;
	//MPI_Status st;
	
	begin(&argc, &argv, &comm, &np, &iam);
	
	m = 20;
	for (i = 0; i<m; i++)
	{
		mm[i] = i * iam + 1;
	}
	MPI_Reduce(mm, res, m, MPI_INT, MPI_SUM, 0, comm);
	if(iam == 0)
	{
		printf("\n1st 10 numbers=");
		for(i = 0; i < 10; i++)
			printf("%d, ", res[i]);
		printf("\n");
	}
	
	end();
	return 0;
}