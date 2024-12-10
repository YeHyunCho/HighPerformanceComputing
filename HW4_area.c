#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "mpi.h"

#define gflops(n,ms) (((n*18.0)/(ms/1.0e+3))/1.0e+9)

long millisecond()
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return(1000*tv.tv_sec + tv.tv_usec/1000);
}

double f(double x)
{
   double temp;
   temp = x*x*x+1;
   return 9*x/(temp*temp);
}

int main(int argc, char *argv[])
{
   int np, pid, tag=0;
   long N, i, local_N;
   double a, b, local_A, dx, x, area;
   long start, elapsed;
   MPI_Status status;

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &np);
   MPI_Comm_rank(MPI_COMM_WORLD, &pid);

   if (argc != 2)
   {
      fprintf(stderr, "usage: %s N\n", argv[0]);
      MPI_Finalize();
      exit(1);
   }

   N = atol(argv[1]);

   start = millisecond();
   a = 0.0;
   b = 2.0;
   dx = (b-a)/N;

   local_N = N/np;
   local_A = 0.0;

   x = ((b-a)/(double)np)*(double)pid;

   // Calculate local area
   for (i=0; i<local_N; i++) {
      local_A += 0.5*(f(x)+f(x+dx))*dx;
      x += dx;
   }

   // Add local areas onto area on P0
   if (pid != 0) {
      MPI_Send(&local_A, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
   }
   else {
      area = local_A;
      for (i=1; i<np; i++) {
         MPI_Recv(&local_A, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status);
         area += local_A;
      }

      // print elapsed time and GFLOPS
      elapsed = millisecond() - start;
      printf("area : %5.10lf\n", area);

      printf("elapsed time : %ld milliseconds", elapsed);
      printf(" (GFLOPS: %5.2lf)\n", gflops(N, elapsed));
   }

   MPI_Finalize();
}
