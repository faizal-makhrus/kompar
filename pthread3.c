#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define num_thread 4
#define num_sum 10000000

int data[num_sum];
long int sum=0;
pthread_mutex_t lock; 

void *Sum(void *arg)
{
    int myid = (int)arg;
	int i;
	int range = floor(num_sum/num_thread);
	long int temp=0;
	
	for (i=myid*range; i< myid*range+range;i++)
	{
		temp+= data[i];
	}
	
	pthread_mutex_lock(&lock);
	sum += temp;					//mutex sejumlah thread
	pthread_mutex_unlock(&lock);
	
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
 
	if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
 
	start = clock();
    for (i = 0; i < num_thread; i++)
        pthread_create(&tid, NULL, &Sum, (void *)i);
    end = clock();
    
    for (i = 0; i < num_thread; i++)
		pthread_join(tid,NULL);			//blocking untuk eksekusi thread berikutnya sampai semua thread terminate
		
	time_dif = (end - start)*1000/CLOCKS_PER_SEC;
	
	//sleep(1);
	printf("Running time: %d and the sum=%ld\n", time_dif, sum);	//perlu dicari solusinya
    
    pthread_mutex_destroy(&lock); 
    pthread_exit(NULL);
    
    return 0; 
}
