#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define num_thread 4
#define num_sum 10000000

int data[num_sum];		//shared memory
long int sum=0;			//shared memory

void *Sum(void *arg)
{
    int myid = (int)arg;	//private mem
	int i;					//private mem
	int range = floor(num_sum/num_thread);	//private mem
	
	for (i=myid*range; i< myid*range+range;i++)
	{
		sum+= data[i];		//sum = sum + data[i] --> race condition
	}
    
    printf("Thread ID: %d, range=%d, sum=%ld\n", myid, range, sum);
}
 
int main()
{
	clock_t start, end;
    int time_dif;
    int i;
    pthread_t tid;
    
    for (i=0; i<num_sum; i++)
		data[i] = i;
 
	start = clock();
    for (i = 0; i < num_thread; i++)
        pthread_create(&tid, NULL, &Sum, (void *)i);
    end = clock();
    
    for (i = 0; i < num_thread; i++)
		pthread_join(tid,NULL);
	time_dif = (end - start)*1000/CLOCKS_PER_SEC;
	
	printf("Running time: %d and the sum=%ld\n", time_dif, sum);
    
    pthread_exit(NULL);
    return 0; 
}
