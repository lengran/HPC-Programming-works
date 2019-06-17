#include "myhead.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int m;

	begin(&argc, &argv, &comm, &np, &iam);

	broadcast(iam, &m, comm);

	end();
	return 0;
}
