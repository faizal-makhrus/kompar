#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#define num_thread 4
#define num_sum 10000000

void *Sum(void *arg)
{
    int myid = (int)arg;
	int i;
	long int sum=0;
	int range = floor(num_sum/num_thread);//jika ada 4 thread dan 10^7 data maka tiap thread sum(2.500.000)
	
	for (i=myid*range; i< myid*range+range;i++)
		sum+=i;
    
    printf("Thread ID: %d, range=%d, sum=%ld\n", myid, range, sum);
}
 
int main()
{
	clock_t start, end;
    int time_dif;
    int i;
    pthread_t tid;
 
	start = clock();
    for (i = 0; i < num_thread; i++)
        pthread_create(&tid, NULL, &Sum, (void *)i);		//Sum(0), Sum(1), Sum(2), Sum(3)
    end = clock();
    
    for (i = 0; i < num_thread; i++)
		pthread_join(tid,NULL);
	time_dif = (end - start)*1000/CLOCKS_PER_SEC;
	
	printf("Running time: %d\n", time_dif);
    
    pthread_exit(NULL);
    return 0; 
}
