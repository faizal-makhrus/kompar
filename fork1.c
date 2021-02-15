#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define n 1000000

int total;

int main(int argc, char **argv)
{
    printf("--beginning of program\n");
    
    int data[n];
    clock_t start, end;
    int time_dif;
    pid_t pid;
    int i,j,k;
    for (i=0; i<n; i++)
		data[i] = i;		//1+rand()%10;
    
	//=======part 1========
	//pid=fork();										
	//if (pid >= 0)			//dijalankan oleh 2 buah proses
	//{
		//printf("process in part 1: pid=%d\n", pid);
		//for (j=0; j<n+100000000;j++)
			//printf("test");
	//}
	//=======end part 1====
	
	//=======part 2========
	//pid=fork();
	//pid=fork();
	//printf("process in part 2: pid=%d\n", pid);			//setiap fork() menciptakan sebuah proses baru.
	//if (pid >= 0)			//dijalankan oleh 2 buah proses
	//{
		//printf("process in part 1: pid=%d\n", pid);
		//for (j=0; j<n+100000000;j++)
			//printf("PID=%d",pid);
	//}
	//=======end part 2====
	
	////=======part 3:serial========
	//int sum=0;
	//start = clock();
	//for (i=0; i<n; i++)
		//sum += data[i];
	//end = clock();
	//time_dif = (end - start)*1000/CLOCKS_PER_SEC;
	//printf("waktu yang dibutuhkan = %d \n", time_dif);
	////=======end part 3===========
	
	//=======part 4: parallel=====		//TUGAS integral f(x)=x^2 dari x=1 s/d x=5 dengan trapesium. dx silakan ditentukan sendiri (misal: 0.000001)
	int sum=0;
	pid = fork();
	
	if (pid == 0)
	{
		start = clock();
		for (i=0; i<floor(n/2); i++)
			sum += data[i];
		
		total = total + sum;
		printf("sum di parent=%d \n", sum);
		printf("total di child=%d \n", total);
		end = clock();
	}
	
	else if (pid > 0)		//child
	{
		start = clock();
		for (i=floor(n/2); i<n; i++)
			sum += data[i];
		
		//sleep(1);				//???
		total = total + sum;
		printf("sum di child=%d \n", sum);
		printf("total di child=%d \n", total);
		end = clock();
		//exit(0);
	}
	
	printf("total=%d \n", total);
	
	time_dif = (end - start)*1000/CLOCKS_PER_SEC;
	printf("waktu yang dibutuhkan = %d \n", time_dif);
	//========end part 4=======

    return 0;
}
