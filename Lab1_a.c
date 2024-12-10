#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long double CalculateFunction(long double xn)
{
   long double yn = xn / ((xn * xn + 2) * (xn * xn + 2) * (xn * xn + 2));

   return yn;
}

main(int argc, char *argv[])
{
   long N;
   long double sum = 0.0; // 모든 사다리꼴의 합

   long double a = 0;
   long double b = 2; //[0, 2] 구간

   long double dx; // 높이
   long double x = a; // 나눠진 구간의 x좌표
   
   int i = 0;
   
   if (argc != 2) 
   {
      printf("argument error\n");
      exit(1);
   }

   N = atol(argv[1]);

   dx = (b-a) / N;
  
   for (i = 0; i < N; i++)
   {
      sum += 0.5 * (CalculateFunction(x) + CalculateFunction(x + dx)) * dx;
      x += dx;
   }
   
   printf("%lf\n", sum;)  
}
