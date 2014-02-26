#include<stdio.h>

void main(){
	float average(float array[],int n);
	float score_1[5] = {98.5,97,91.5,60,55};
	float score_2[10] = {67.5,89.5,99,69.5,77,89.5,76.5,54,60,99.5};
	int i;
	printf("Get the array a store address in main function:\n");
	for(i=0;i<5;i++){
		printf("%d  ",&score_1[i]);
	}
	printf("\nGet the array b store address in main function:\n");
	for(i=0;i<10;i++){
		printf("%d  ",&score_2[i]);
	}
	printf("\nThe average of class A is %6.2f",average(score_1,5));
	printf("\nThe average of class B is %6.2f\n",average(score_2,10));
}

float average(float arr[],int n){
	int i;
	float sum=0;
	printf("\nGet the array store address in callee function:\n");
	for(i=0;i<n;i++){
		sum+= arr[i];
		printf("%d  ",&arr[i]);
	}
	return sum/n;
}