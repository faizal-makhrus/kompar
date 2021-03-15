#include <stdio.h>
#define N 10000

__global__ void add(int *a, int *b, int *c)		//tidak ada operasi di CPU. Ada 10 threads
{
	int tID= threadIdx.x;		//tID = selalu 1, namun blockID = menyesuaikan
	if (tID < N)
	{
		c[tID] = a[tID] + b[tID];		//blockID=0, tID=0, menjumlahkan a[0] dan b[0],
										//blockID=1, tID=0, menjumlahkan a[1] dan b[1],
										//blockID=2, tID=0, menjumlahkan a[2] dan b[2], dst.
	}
}

int main()
{
	int *a, *b, *c;
	a = (int*)malloc(N*sizeof(int));
	b = (int*)malloc(N*sizeof(int));
	c = (int*)malloc(N*sizeof(int));
	int *dev_a, *dev_b, *dev_c;
	
	cudaMalloc((void **) &dev_a, N*sizeof(int));
	cudaMalloc((void **) &dev_b, N*sizeof(int));
	cudaMalloc((void **) &dev_c, N*sizeof(int));// Fill Arrays
	
	for (int i = 0; i < N; i++)
	{
		a[i] = i, b[i] = 1;		//CPU
	}
	
	cudaMemcpy(dev_a, a, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, N*sizeof(int), cudaMemcpyHostToDevice);
	add<<<1,N>>>(dev_a, dev_b, dev_c);
	cudaMemcpy(c, dev_c, N*sizeof(int), cudaMemcpyDeviceToHost);
	
	for (int i = 0; i < N; i++)
	{
		printf("%d + %d = %d\n", a[i], b[i], c[i]);
	}
	
	return 0;
}
