#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#define M 12
#define N 10

float **malloc_2d();
void grid();

int main(int argc, char* argv[])
{
   float A[M][N], B[M][N], C[M][N], **local_A, **local_B, **local_C;
   int np, inp, jnp, pid, local_M, local_N, *displs, *counts, i, j, n, tag=0;
   MPI_Status status;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &np);
   MPI_Comm_rank(MPI_COMM_WORLD, &pid);

   grid(M, N, np, pid, &inp, &jnp);
   if (pid==0) printf("%dx%d processors are used\n", inp, jnp);

   local_M = M/inp;
   local_N = N/jnp;

   // Initialization of A and B
   if (pid==0) {
      for (i=0; i<M; i++)
         for (j=0; j<N; j++) {
            A[i][j] = i*N;
            B[i][j] = j;
         }
   }

   local_A = malloc_2d(local_M, local_N);
   local_B = malloc_2d(local_M, local_N);
   local_C = malloc_2d(local_M, local_N);

   // (1) Decompose A and B into local_A and local_B
   displs = (int*)malloc(sizeof(int)*np);
   counts = (int*)malloc(sizeof(int)*np);

   for(i=0; i<np; i++) {
      displs[i] = i * local_M * local_N;
      counts[i] = local_M * local_N;
   }

   MPI_Scatterv(&A[0][0], counts, displs, MPI_FLOAT, &local_A[0][0], local_M*local_N, MPI_FLOAT, 0, MPI_COMM_WORLD);
   MPI_Scatterv(&B[0][0], counts, displs, MPI_FLOAT, &local_B[0][0], local_M*local_N, MPI_FLOAT, 0, MPI_COMM_WORLD);

   // (2) local_C = local_A + local_B
   for (i=0; i<local_M; i++)
      for (j=0; j<local_N; j++)
         local_C[i][j] = local_A[i][j] + local_B[i][j];

   // (3) Compose local_C to C
   MPI_Gatherv(&local_C[0][0], local_M*local_N, MPI_FLOAT, &C[0][0], counts, displs, MPI_FLOAT, 0, MPI_COMM_WORLD);

   // Print the results
   if (pid==0)
      for (i=0; i<M; i++) {
         for (j=0; j<N; j++)
            printf("%3.0f", C[i][j]);
         printf("\n");
      }

   free(local_A);
   free(local_B);
   free(local_C);
   free(displs);
   free(counts);

   MPI_Finalize();
}
