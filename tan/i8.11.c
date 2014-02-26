#include<stdio.h>

void main(){
	float aver;
	float average(float array[]);
	int i,amount=10;
	float score[10] = {100,56,78,98.5,76,87,99,67.5,75,97};
	printf("List the array:");
	for(i=0;i<amount;i++){
		printf("%6.2f",score[i]);
	}
	//if you use score[10],you will get error: type is not compatible with formal params and exact params.
	//score[10] is a val,not a array
	aver = average(score);
	printf("\nthe average score is %5.2f", aver);
	printf("\nthe average score is %5.2f", average(score));
}

float average(float array[10]){
	int i;
	float aver,sum = 0;
	for(i=0;i<10;i++){
		sum+=array[i];
	}
	aver = sum/10;
	return aver;
}