#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<omp.h>
#define SIZE 80000
#define NUM_THREADS 80

int main(){
int i;
int minNumber;
double start;  
double end;  
double eTime;
int tid, private_min;
int res[8] ={0};
int min = INT_MAX;
int *arr = (int *)malloc(SIZE * sizeof(int));
srand(0);

for(i=0; i<SIZE; i++){
arr[i] = rand() % 1000;
}

start = omp_get_wtime();

#pragma omp parallel num_threads(2) private(tid, private_min) //cyclic distribution
{

 tid = omp_get_thread_num();
 private_min = arr[tid];
 for(int i=tid;i<SIZE;i+=NUM_THREADS){
	//printf("my id is%d i am operatin on %d\n",tid,arr[i]);
	if(private_min > arr[i])
		private_min = arr[i];
}
//printf("\nmy id is %d private_min is %d\n",tid, private_min);
res[tid] = private_min;
}


for(int i=0;i<2;i++){
	if(res[i] < min)
		min = res[i];
}
printf("%d ", min);	
end = omp_get_wtime();
eTime = end - start;
printf("%lf", eTime);
return 0;
}
