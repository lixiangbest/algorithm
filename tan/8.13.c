#include<stdio.h>

void main(){
	int n;
	float x;
	float px(float,int);
	printf("Please enter x,n:\n");
	scanf("%f %d",&x,&n);
	printf("%6.3f",px(x,n));
}

float px(float x,int n){
	float val;
	if(n==0){
		return 0;
	}else if(n==1){
		return x;
	}else{
		val = (2*(n-1)*x-px(x,n-1)-(n-1)*px(x,n-2))/n;
		return val;
	}
}