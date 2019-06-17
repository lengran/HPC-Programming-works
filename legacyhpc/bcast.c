#include "myhead.h"

void broadcast(int iam, int *m, MPI_Comm comm)
{
	if(iam ==0) *m =111;
	else *m = 0;
	MPI_Bcast (m, 1, MPI_INT, 1 , comm);

	printf("\n Value in proc%d is %d!\n", iam, *m);
}
