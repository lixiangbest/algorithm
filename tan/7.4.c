#include<stdio.h>

void main(){
	int orders[9] = {1,5,7,9,10,14,19,28};
	int i,amount=9,insert=9,exchange;
	printf("Befor ordered:");
	for(i=0;i<amount;i++){
		printf("%3d",orders[i]);
	}
	printf("\nAfter ordered:");
	for(i=0;i<amount;i++){
		if(orders[i]>insert||i==amount-1){
			exchange = insert;
			insert = orders[i];
			orders[i] = exchange;
		}
	}
	for(i=0;i<amount;i++){
		printf("%3d",orders[i]);
	}
}