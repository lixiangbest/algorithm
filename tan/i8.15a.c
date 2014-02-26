#include<stdio.h>

float Max = 0, Min = 0;//global variables,it is used to get three return values.
float average(float array[],int n){//formal parameter is array.
	int i;
	float aver, sum = 0;
	Max = Min = array[0];
	for(i=0;i<n;i++){
		if(array[i]>Max) Max = array[i];
		else if(array[i]<Min) Min = array[i];
		sum = sum + array[i];
	}
	aver = sum/n;
	return(aver);
}

void main(){
	float ave, score[10] = {99,45,78,97,100,67.5,89,92,66,43};
	int i;
	printf("The array is:\n");
	for(i=0;i<10;i++){
		printf("%6.2f ",score[i]);
	}
	ave = average(score,10);
	printf("\nmax=%6.2f min=%6.2f average=%6.2f\n",Max,Min,ave);
}