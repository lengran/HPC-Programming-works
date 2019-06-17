#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	// Print out hello world in each process
	MPI_Comm comm;
	int np, iam;

	MPI_Init(&argc, &argv);
	MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Comm_size(comm, &np);
	MPI_Comm_rank(comm, &iam);
	
	// main body
	printf("\nHello world from %d!", iam);
	
	// Terminate
	MPI_Finalize();
	
	return 0;
}
// Build the common lines to a library to avoid compiling these stuff everytime u need them!
