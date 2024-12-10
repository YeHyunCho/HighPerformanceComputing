#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
   int np, pid, inp, jnp, i, j, k, *buf;
   int dim_sizes[2], wrap_around[2];
   int direct, shift, source, dest, reorder, tag=0;
   MPI_Comm grid_comm;
   MPI_Status status;

   int coordinates[2];

   MPI_Group diag_world;
   MPI_Group diag_group;
   MPI_Comm diag_comm;
   int *diag_rank;
   int data;
   int pid_from;

   MPI_Init(&argc, &argv);

   MPI_Comm_rank(MPI_COMM_WORLD, &pid);
   MPI_Comm_size(MPI_COMM_WORLD, &np);

   inp = sqrt(np);
   // Check np is a square number
   if(np!=inp*inp) {
      if(pid==0) fprintf(stderr, "#proc is not a square number of 2\n");
      MPI_Finalize();
      exit(0);
   }

   jnp = np/inp;
   dim_sizes[0] = inp;
   dim_sizes[1] = jnp;
   wrap_around[0] = wrap_around[1] = 1;

   MPI_Cart_create(MPI_COMM_WORLD, 2, dim_sizes, wrap_around, reorder, &grid_comm);
   MPI_Cart_coords(grid_comm, pid, 2, coordinates);

   // new communicator and broadcast
   diag_rank = (int*)malloc(inp*sizeof(int));
   for(i=0; i<jnp; i++)
      diag_rank[i] = i * (jnp + 1);

   MPI_Comm_group(MPI_COMM_WORLD, &diag_world);
   MPI_Group_incl(diag_world, inp, diag_rank, &diag_group);
   MPI_Comm_create(MPI_COMM_WORLD, diag_group, &diag_comm);

   data = pid;
   if(coordinates[0]+coordinates[1]==3) {
      printf("[0] = %d, [1] = %d\n", coordinates[0], coordinates[1]);
      MPI_Bcast(&data, 1, MPI_INT, jnp-1, diag_comm);
   }
   // Print the shifted matrix
   if(pid==0)
      buf = (int *)malloc(sizeof(int)*np);

   MPI_Gather(&pid_from, 1, MPI_INT, buf, 1, MPI_INT, 0, MPI_COMM_WORLD);

   if (pid==0) {
      k = 0;
      for(i=0; i<inp; i++) {
         for(j=0; j<jnp; j++)
            printf("%2d ", buf[k++]);
         printf("\n");
      }
      free(buf);
   }

   MPI_Finalize();
   exit(0);
}
