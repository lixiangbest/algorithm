#include<stdio.h>

void main(){
	int prime[100];
	int i,j,amount=100;
	for(i=0;i<amount;i++){
		prime[i] = i+1;
	}
	for(i=0;i<amount;i++){
		if(prime[i]==1||prime[i]==0) continue;
		//get the mod
		for(j=i+1;j<amount;j++){
			if(prime[j]%prime[i]==0){
				prime[j]=0;
			}
		}
	}
	//output
	for(i=0;i<amount;i++){
		if(prime[i]==0||prime[i]==1) continue;
		else printf("%5d ",prime[i]);
	}
}