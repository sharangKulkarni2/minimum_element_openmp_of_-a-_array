#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<omp.h>
#define SIZE 100
#define NUM_THREADS 10

void main(){

int i;
int minNumber;
double start;  
double end;  
double eTime;
int private_min;
int tid;
int res[NUM_THREADS] ={0};
int min = INT_MAX;
int *arr = (int *)malloc(SIZE * sizeof(int));

srand(0);

for(i=0; i<SIZE; i++){
arr[i] = rand() % 1000;
}

start = omp_get_wtime();
#pragma omp parallel num_threads(NUM_THREADS) private(private_min)
{	
	private_min = INT_MAX;
	//printf("BEFORE thread id: %d private min is :%d\n",omp_get_thread_num(), private_min);

#pragma omp for schedule(static, 1)
	for(i=0; i<SIZE; i++){
		//printf("thread id: %d i:%d\n", omp_get_thread_num(), i);
		if(arr[i] < private_min)
			private_min = arr[i];
	}

	tid = omp_get_thread_num();
	//printf("AFTER thread id: %d private min is :%d\n",omp_get_thread_num(), private_min);
	res[tid] = private_min;
	
}

for(i=0;i<NUM_THREADS;i++){
	//printf("%d\n", res[i]);
	if(res[i] < min)
		min = res[i];
}

	end = omp_get_wtime();	
	eTime = end - start;

	printf("min :%d\n",min);
	printf("time : %lf", eTime);

}
