#include "myhead.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam, i;
	float a[16], b[16], c[16];

	begin(&argc, &argv, &comm, &np, &iam);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			a[i * 4 + j] = i + j;
			b[j * 4 + i] = i + j;
		}

	matrmul(comm, np, iam, a, b, c, 4, 4, 4);

	if (iam == 0)
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				printf("%f\t", c[i * 4 + j]);
			printf("\n");
		}

	end();
	return 0;
}
