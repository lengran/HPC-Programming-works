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
	mm[0] = iam + 1;
	if (iam == 1) mm[0] = 111;
	mm[1] = iam;
	MPI_Reduce(mm, res, 1, MPI_2INT, MPI_MAXLOC, 0, comm);
	if(iam == 0)
	{
		printf("\nmax = %d, %d\n", res[0], res[1]);
	}
	
	end();
	return 0;
}