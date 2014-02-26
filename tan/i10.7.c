#include<stdio.h>
#define Total 10
void intv(int x[],int n){
	int temp,i,j,m=(n-1)/2;
	for(i=0;i<=m;i++){
		j=n-1-i;
		temp=x[i];
		x[i]=x[j];
		x[j]=temp;
	}
}

void pintv(int *x,int n){
	int *p,temp,*i,*j,m=(n-1)/2;
	i=x;//first value address
	j=x+n-1;//last value address
	p=x+m;//middle value address
	for(;i<=p;i++,j--){
		temp = *i;
		*i = *j;
		*j = temp;
	}
	return;
}

void main(){
	int i,a[Total]={3,7,9,11,0,6,7,5,4,2};
	printf("The original array:\n");
	for(i=0;i<Total;i++){
		printf("%d,",a[i]);
	}
	printf("\n");
	intv(a,Total);
	printf("The array has been inverted using array variable:\n");
	for(i=0;i<Total;i++){
		printf("%d,",a[i]);
	}
	printf("\n");
	pintv(a,Total);
	printf("The array has been inverted using pointer variable:\n");
	for(i=0;i<Total;i++){
		printf("%d,",a[i]);
	}
	printf("\n");
}