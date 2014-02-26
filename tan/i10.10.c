#include<stdio.h>
#define Total 10

void main(){
	int *p,i,a[Total]={10,14,24,15,17,27,29,30,35,40};
	void sorted(int*,int);
	p = a;
	printf("The original array:\n");
	for(i=0;i<Total;i++){
		printf("%d ",*p++);
	}
	p = a;
	printf("\nThe size of pointer p:%d",sizeof(p));//p is pointer,storing the address of a[0];
	printf("\nThe size of array a:%d",sizeof(a));//a is array,it has 40 bytes(4*10)
	sorted(p,Total);
	printf("\nThe sorted array:\n");
	for(p=a;p<a+Total;){
		printf("%d ",*p++);
	}
}

void sorted(int x[],int n){
	int i,j,k,t;
	for(i=0;i<n-1;i++){
		k=i;
		for(j=i+1;j<n;j++){
			if(x[j]>x[k]) k = j;
		}
		if(k!=i){
			t = x[i];
			x[i] = x[k];
			x[k] = t;
		}
	}
	x = x+9;
	printf("\nThe current value of x pointer is:%d",*x);
}