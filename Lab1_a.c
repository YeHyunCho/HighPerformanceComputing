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
   long double sum = 0.0; // ��� ��ٸ����� ��

   long double a = 0;
   long double b = 2; //[0, 2] ����

   long double dx; // ����
   long double x = a; // ������ ������ x��ǥ
   
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
