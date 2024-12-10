#include <stdio.h>

#define N 12
#define A(i,j) A[i*N+j]

__global__ void gradual(int *A)
{
   int i = blockIdx.x * blockDim.x + threadIdx.x;
   int j = blockIdx.y * blockDim.y + threadIdx.y;

   if (i >= j)
      A(i, j) = i;
   else
      A(i, j) = j;
}

int main(int argc, char *argv[])
{
   int A[N][N], *A_d;
   int nt, i, j, dev;

   // GPU info
   cudaDeviceProp deviceProp;

   dev = 1;
   cudaSetDevice(dev);
   cudaGetDevice(&dev);
   cudaGetDeviceProperties(&deviceProp, dev);
   printf("Using Device %d: \"%s\"\n", dev, deviceProp.name);

   if (argc != 2) {
      fprintf(stderr, "usage: %s #threads\n", argv[0]);
      exit(1);
   }

   nt = atoi(argv[1]);

   dim3 dimBlock(nt, nt);
   dim3 dimGrid(N/nt, N/nt);

   cudaMalloc((void **) &A_d, sizeof(float)*N*N);

   gradual<<<dimGrid, dimBlock>>>(A_d);

   cudaMemcpy(A, A_d, sizeof(float)*N*N, cudaMemcpyDeviceToHost);

   for(i=0; i<N; i++) {
      for (j=0; j<N; j++)
         printf("%3d ", A[i][j]);
      printf("\n");
   }

   cudaFree(A_d);

}
