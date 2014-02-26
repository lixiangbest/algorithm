#include<stdio.h>

void main(){
	int elems[3][3]={{8,27,30},{4,5,2},{17,19,24}};
	int evens[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	int sum=0;
	sum=oddSum(elems,3);
	printf("sum=%d\n",sum);
	sum=evenSum(evens,4);
	printf("sum=%d\n",sum);
}

//sum diagonal line value of array.
int evenSum(int val[][4],int amount){
	int i,j,sum=0;
	for(i=0;i<amount;i++){
		sum+=val[i][i];
		sum+=val[i][amount-i-1];
	}
	//if even array
	if(amount%2==0){
		return sum;
	}else{
		//odd should minus an repeated middle number
		return sum-val[amount/2][amount/2];
	}
}

//sum diagonal line value of array.
int oddSum(int val[][3],int amount){
	int i,j,sum=0;
	for(i=0;i<amount;i++){
		sum+=val[i][i];
		sum+=val[i][amount-i-1];
	}
	//if even array
	if(amount%2==0){
		return sum;
	}else{
		//odd should minus an repeated middle number
		return sum-val[amount/2][amount/2];
	}
}
