#include<stdio.h>

void main(){
	int orders[10] = {1,5,7,9,10,14,19,28,30,35};
	int evens[9] = {1,5,7,9,10,14,19,28,30};
	int i,amount=10,count=9,exchange;
	printf("1.Before exchanged:");
	for(i=0;i<amount;i++){
		printf("%3d",orders[i]);
	}
	printf("\n1.After  exchanged:");
	for(i=0;i<amount/2;i++){
		exchange = orders[i];
		orders[i] = orders[amount-i-1];
		orders[amount-i-1] = exchange;
	}
	for(i=0;i<amount;i++){
		printf("%3d",orders[i]);
	}
	
	printf("\n2.Before exchanged:");
	for(i=0;i<count;i++){
		printf("%3d",evens[i]);
	}
	printf("\n2.After  exchanged:");
	for(i=0;i<count/2;i++){
		exchange = evens[i];
		evens[i] = evens[count-i-1];
		evens[count-i-1] = exchange;
	}
	for(i=0;i<count;i++){
		printf("%3d",evens[i]);
	}
}