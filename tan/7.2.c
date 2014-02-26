#include<stdio.h>

void main(){
	int orders[10]={8,27,30,4,5,2,17,19,24,35};
	int i,j,amount=10,min,ex,position;
	printf("Order before:");
	for(i=0;i<amount;i++){
		printf("%5d",orders[i]);
	}
	for(i=0;i<amount-1;i++){
		min = orders[i];
		for(j=i+1;j<amount;j++){
			if(orders[j]<min){
				min = orders[j];
				position=j;
			}
		}
		ex = orders[position];
		orders[position] = orders[i];
		orders[i] = ex;
	}
	printf("\nOrder after:");
	for(i=0;i<amount;i++){
		printf("%5d",orders[i]);
	}
}
