#include <stdio.h>

#define M 12
#define N 10
#define A(i,j) A[i*N+j]
#define B(i,j) B[i*N+j]
#define C(i,j) C[i*N+j]

__global__ void matadd(float *A, float *B, float *C)
{
   int i = blockDim.x * blockIdx.x + threadIdx.x;
   int j = blockDim.y * blockIdx.y + threadIdx.y;
   
   if (i<M && j<N)
      C(i,j) = A(i,j) + B(i,j);
}

int main(int argc, char *argv[])
{
   float A[M][N], B[M][N], C[M][N];
   float *A_d, *B_d, *C_d;
   int THREADS_M, THREADS_N, i, j, dev;

   cudaDeviceProp deviceProp;

   dev = 1;
   cudaSetDevice(dev);
   cudaGetDevice(&dev);
   cudaGetDeviceProperties(&deviceProp, dev);

   printf("Using Device %d: \"%s\"\n", dev, deviceProp.name);

   if(argc != 3) {
      fprintf(stderr, "usage: %s threads_M threads_N\n", argv[0]);
      exit(1);
   }

   THREADS_M = atol(argv[1]);
   THREADS_N = atoi(argv[2]);

   // Initialization of A and B
   for (i=0; i<M; i++)
      for (j=0; j<N; j++) {
         A[i][j] = M - i + 1;
         B[i][j] = N + j;
      }

   // Call matadd kenel
   dim3 dimBlock(THREADS_M, THREADS_N);
   dim3 dimGrid(M/THREADS_M, N/THREADS_N);

   cudaMalloc((void **) &A_d, sizeof(float)*M*N);
   cudaMalloc((void **) &B_d, sizeof(float)*M*N);
   cudaMalloc((void **) &C_d, sizeof(float)*M*N);

   cudaMemcpy(A_d, A, sizeof(float)*M*N, cudaMemcpyHostToDevice);
   cudaMemcpy(B_d, B, sizeof(float)*M*N, cudaMemcpyHostToDevice);

   matadd<<<dimGrid, dimBlock>>>(A_d, B_d, C_d);

   cudaMemcpy(C, C_d, sizeof(float)*M*N, cudaMemcpyDeviceToHost);

   // Print the results
   for(i=0; i<M; i++) {
      for(j=0; j<N; j++)
         printf("%3.0f", C[i][j]);
      printf("\n");
   }
   
   cudaFree(A_d);
   cudaFree(B_d);
   cudaFree(C_d);

   exit(0);
}
