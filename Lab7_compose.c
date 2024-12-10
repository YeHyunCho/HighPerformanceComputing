#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#define N 24

int **malloc_2d(int row, int col)
{
   int **A, *ptr;
   int len, i;

   len = sizeof(float *)*row + sizeof(float)*col*row;
   A = (int **)malloc(len);
   ptr = (int *)(A+row);

   for(i=0; i<row; i++)
      A[i] = (ptr+col*i);

   return A;
}

main(int argc, char* argv[])
{
   int A[N][N], **local_A;
   int np2, np, pid, local_N, i, j, x, y;
   MPI_Status status;
   int tag=0;
   MPI_Datatype vector_t;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &pid);
   MPI_Comm_size(MPI_COMM_WORLD, &np2);
   
   np = sqrt(np2);
   local_N = N/np;

   local_A = malloc_2d(local_N, local_N);

   // Initialization of arrays
   if (pid == 0) {
      for(i=0; i<local_N; i++)
         for (j=0; j<local_N; j++)
            A[i][j] = pid;
   }
   else {
      for (i=0; i<local_N; i++)
         for (j=0; j<local_N; j++)
            local_A[i][j] = pid;
   }

   // Composition
   if (pid != 0) {
      MPI_Send(&local_A[0][0], local_N*local_N, MPI_INT, 0, tag, MPI_COMM_WORLD);
   }
   else {
      MPI_Type_vector(local_N, local_N, N, MPI_INT, &vector_t);
      MPI_Type_commit(&vector_t);

      for (j=1; j<np2; j++) {
         x = (j/np) * local_N;
         y = (j%np) * local_N;
         MPI_Recv(&A[x][y], 1, vector_t, j, tag, MPI_COMM_WORLD, &status);
      }
   }

   // Print the result
   if (pid == 0)
      for(i=0; i<N; i++) {
         for (j=0; j<N; j++)
            printf("%3d", A[i][j]);
         printf("\n");
      }

   free(local_A);
   MPI_Finalize();
}
