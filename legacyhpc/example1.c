#include "myhead.h"

int main(int argc, char **argv)
{
	// Print out hello world in each process
	int np, iam;
	MPI_Comm comm;
	
	mybegin(&argc, &argv, &comm, &np, &iam);	
	
	// main body
	printf("\nHello world from %d!", iam);
	
	// Terminate
	myend();
	
	return 0;
}
// Build the common lines to a library to avoid compiling these stuff everytime u need them!
