#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<omp.h>
#define SIZE 80000
int main(){
int i;
int minNumber;
double start;  
double end;  
double eTime;
int *arr = (int *)malloc(SIZE * sizeof(int));
srand(0);
for(i=0; i<SIZE; i++){
arr[i] = rand() % 1000;
}
start = omp_get_wtime();
minNumber = arr[0];
for(i=1; i<SIZE; i++){
 if(minNumber > arr[i])
 	minNumber = arr[i];
 }
end = omp_get_wtime();
eTime = end - start;
printf("%d is min and time ",minNumber);
printf("%lf", eTime);
return 0;
}
