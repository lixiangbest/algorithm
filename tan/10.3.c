#include<stdio.h>
#define Total 5

void main(){
	void enter(int*);
	void handle(int*);
	void print(int*);
	int a[Total];
	enter(a);
	handle(a);
	print(a);
}

void enter(int *p){
	int i;
	for(i=0;i<Total;i++){
		printf("Enter the %d integer:",i);
		scanf("%d",p++);
	}
}

void handle(int *p){
	int i,min=0,max=0,temp;
	for(i=1;i<Total;i++){
		if(*(p+i)<*(p+min)) min = i;
		if(*(p+i)>*(p+max)) max = i;
	}
	if(min!=0){
		temp = *(p+min);
		*(p+min) = *p;
		*p = temp;
	}
	if(max!=Total-1){
		temp = *(p+max);
		*(p+max) = *(p+Total-1);
		*(p+Total-1) = temp;
	}
}

void print(int *p){
	int i;
	for(i=0;i<Total;i++){
		printf("%3d",*p++);
	}
}