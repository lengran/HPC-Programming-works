#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void begin(int *argc, char ***argv, MPI_Comm *comm, int *np, int *iam);
void end();
void scan(int n, float *x, float *y, int iam, int np, MPI_Comm comm);
void scatter(MPI_Comm comm, int blk, float *a);
void transpose(float * a, int m, int n);
void matrmul(MPI_Comm comm, int np, int iam, float *a, float *b, float *c, int m, int n, int k);
