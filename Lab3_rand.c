#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define range(n) ((unsigned int)((n)/65535)%32758)
#define N 1000

int next = 1;

int rand2(int a, int c)
{
   return (next = next * a + c);
}

void srand2(int seed)
{
   next = seed;
}

int main(int argc, char *argv[])
{
   int X[N], Y[N], nt, tid, local_N, i, j, sum_X, sum_Y;
   int a, c, A, C;

   if (argc != 2)
   {
      printf("usage: %s #treas\n", argv[0]);
      exit(1);
   }
   
   nt = atoi(argv[1]);

   srand2(1);
   a = 1103515245;
   c = 12345;

   sum_X = 0;

   for (i=0; i<N; i++)
   {
      X[i] = rand2(a, c);
      sum_X += range(X[i]);
   }

   local_N = N/nt;

   srand2(1);
   for (i=0; i<N; i+=local_N)
   {
      Y[i] = rand2(a, c);
   }

   A = 1; C = 0;
 
   for (i=0; i<nt; i++)
   {
      A = (a * A);
      C = (a * C + c);
   }

   sum_Y = 0;
   
   #pragma omp parrel for reduction(+:sum_Y) private(i) num_threads(nt)
   for (i=0; i<N; i++)
   {
      if(!(i%local_N)) srand2(Y[i]);
      else Y[i] = rand2(A, C);
     
      sum_Y = sum_Y + range(Y[i]);
   }

   printf("Sum of X is %u\n\n", sum_X);
   printf("Sum of Y is %u\n\n", sum_Y);
   
   exit(0);
}

