#include "myhead.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam, i;
	float mm[20], res[20], c[40];

	begin(&argc, &argv, &comm, &np, &iam);

	if(iam == 0)
		for(i = 0; i < 40; i++) c[i] = i;

	scatter( comm, 5, &c[0]);
	printf("\nVs are %f, %f, %f in %d\n", c[0], c[1], c[2], iam);

	end();
	return 0;
}
