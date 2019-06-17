#include "myhead.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int mm[20], res[20];

	begin(&argc, &argv, &comm, &np, &iam);

	mm[0] = iam + 1;
	mm[1] = iam;
	
	MPI_Reduce(mm, res, 1, MPI_2INT, MPI_MAXLOC, 0, comm);

	if(iam == 0)
		printf("max = %d, %d\n", res[0], res[1]);

	end();
	return 0;
}
