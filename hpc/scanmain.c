#include "myhead.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	float mm[20], res[20];

	begin(&argc, &argv, &comm, &np, &iam);

	mm[0] = iam + 1;
	mm[1] = iam;

	scan(2, mm, res, iam, np, comm);
	printf("max = %d, %d, p = %d\n", (int)res[0], (int)res[1], iam);

	end();
	return 0;
}
