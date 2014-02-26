#include<stdio.h>
#define N 5

void main(){
	int i,a[N],*p=a;
	void reverse(int*);
	for(i=0;i<N;i++){
		printf("Enter the %d integer:",i);
		scanf("%d",p++);
	}
	printf("reverse array:\n");
	reverse(p);
}

void reverse(int *p){
	int i;
	for(i=N;i>0;i--){
		printf("%3d",*(--p));
	}
}

