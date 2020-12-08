#include "myhead.h"

int main(int argc, char **argv)
{
	MPI_Comm comm;
	int np, iam;
	int mm[20], res[20];

	begin(&argc, &argv, &comm, &np, &iam);

	int sendBuf[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	int recvBuf[20] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	MPI_Datatype tmpdtp, dtp;
	MPI_Status status;

	MPI_Type_contiguous(3, MPI_INT, &tmpdtp);
	//MPI_Type_commit(&tmpdtp);
	MPI_Type_create_resized(tmpdtp, -4, 20, &dtp);
	MPI_Type_commit(&dtp);

	if (iam == 0)
	{
		MPI_Aint lb, extent, real_lb, real_extent;
		MPI_Type_get_extent(dtp, &lb, &extent);
		MPI_Type_get_true_extent(dtp, &real_lb, &real_extent);
		printf("extent = %ld, true extent = %ld, lb = %ld, true lb = %ld\n", extent, real_extent, lb, real_lb);
		MPI_Recv(&recvBuf[1], 4, dtp, 1, 0, comm, &status);
		for (int i = 0; i < 20; i++)
		{
			printf("%d ", recvBuf[i]);
		}
	}
	else
	{
		MPI_Send(&sendBuf[1], 4, dtp, 0, 0, comm);
	}
	

	MPI_Type_free(&dtp);
	//MPI_Type_free(&tmpdtp);
	end();

	return 0;
}
