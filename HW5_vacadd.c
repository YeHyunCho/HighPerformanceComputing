#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N 120

main(int argc, char* argv[])
{
   int np, pid, local_N, i;
   float A[N], B[N], C[N], *local_A, *local_B, *local_C;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &np);
   MPI_Comm_rank(MPI_COMM_WORLD, &pid);

   // Initialization of A and B
   if(pid==0) {
      for(i=0; i<N; i++) {
         A[i]=i;
         B[i]=N-i;
      }
   }

   local_N = N/np;

   local_A = malloc(sizeof(float)*local_N);
   local_B = malloc(sizeof(float)*local_N);
   local_C = malloc(sizeof(float)*local_N);

   // Decomposition
   MPI_Scatter(A, local_N, MPI_FLOAT, local_A, local_N, MPI_FLOAT, 0, MPI_COMM_WORLD);
   MPI_Scatter(B, local_N, MPI_FLOAT, local_B, local_N, MPI_FLOAT, 0, MPI_COMM_WORLD);

   // Addition
   for(i=0; i<local_N; i++)
      local_C[i] = local_A[i] + local_B[i];

   // Composition
   MPI_Gather(local_C, local_N, MPI_FLOAT, C, local_N, MPI_FLOAT, 0, MPI_COMM_WORLD);

   // print results
   if(pid==0) {
      for(i=0; i<N; i++)
         printf("%2.1f ", C[i]);
      printf("\n");
   }

   free(local_A);
   free(local_B);
   free(local_C);

   MPI_Finalize();
}                    
