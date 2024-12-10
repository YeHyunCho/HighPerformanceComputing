#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

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
   long N, i, tid, nt;
   double a, b, area, dx, x;
   long start, elapsed;
	
   if (argc != 3)
   {
      fprintf(stderr, "usage: %s number_of_segments\n", argv[0]);
      exit(1);
   }
	
   N = atol(argv[1]);
   nt = atol(argv[2]);

   printf("sequential running ------\n");

   // Sequential Programming 
   	
   start = millisecond();
   a = 0.0;
   b = 2.0;
   dx = (b-a)/N;
	
   area = 0.0;
   x = a;
   for (i=0; i<N; i++) 
   {
      area += 0.5*(f(x)+f(x+dx))*dx;
      x += dx;
   }
	
   elapsed = millisecond() - start;
   printf("area : %5.10lf\n", area);
	
   printf("elapsed time: %ld milliseconds", elapsed);
   printf(" (GFLOPS: %5.2lf)\n", gflops(N, elapsed));

   printf("\nparallel running ------\n");
   
   // Parallel Programming
 
   start = millisecond();
   
   area = 0.0;
   omp_set_num_threads(nt);
   #pragma omp parallel private(i,x,tid) shared(area)
   {
      tid = omp_get_thread_num();
      x = ((b-a)/nt)*tid;
      
      #pragma omp for reduction(+:area)
      for (i=0; i<N; i++) 
      {
         area += 0.5*(f(x)+f(x+dx))*dx;
         x += dx;
      }
   }
   
   elapsed = millisecond() - start;
   printf("area : %5.10lf\n", area);

   printf("elasped time: %ld milliseconds", elapsed);
   printf(" (GFLOPS: %5.2lf)\n", gflops(N, elapsed));
	
   exit(0);
}
