#include<stdio.h>
#define Total 10

void main(){
	int i,arr[Total]={10,14,24,15,17,27,29,30,35,40},*p = arr;
	void inv(int*,int);
	printf("The original array:\n");
	for(i=0;i<Total;i++,p++){
		printf("%d ",*p);
	}
	printf("\n");
	p = arr;
	inv(p,Total);
	printf("The array has been inverted:\n");
	for(p=arr;p<arr+Total;p++){
		printf("%d ",*p);
	}
	printf("\n");
}

void inv(int *x,int n){
	int *p,m,temp,*i,*j;
	m = (n-1)/2;
	i = x;j = x+n-1;p = x+m;
	printf("The first value is:%d\n",*x);
	for(;i<=p;i++,j--){
		temp = *i;
		*i = *j;
		*j = temp;
	}
}