#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void begin(int *argc, char ***argv, MPI_Comm *comm, int *np, int *iam);
void end();
