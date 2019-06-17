#include "mpi.h"

void scan(n, x, y, iam, np, comm)
int n, iam, np;
float *x, *y;
MPI_Comm comm;
{
    MPI_Group bgrp, sgrp;
    int i, j;
    int ranks[10];
    MPI_Comm tcom;

    MPI_Comm_group(comm, &bgrp);
    for(i = 1; i <= np; i++)
    {
	for(j = 0; j <= i; j++) ranks[j] = j;
	MPI_Group_incl(bgrp, i, ranks, &sgrp);
	MPI_Comm_create(comm, sgrp, &tcom);
	if(iam < i)
	{
            MPI_Reduce(x, y, n, MPI_FLOAT, MPI_SUM, i - 1, tcom);
	}
    }

    MPI_Group_free(&bgrp);
    MPI_Group_free(&sgrp);
    MPI_Comm_free(&tcom);
    return;
}
