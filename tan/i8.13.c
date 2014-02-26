#include<stdio.h>

void sort(int array[],int n){
	int i,j,k,t,m=0;
	for(i=0;i<n-1;i++){
		k = i;
		for(j=i+1;j<n;j++){
			if(array[j]<array[k]) k = j;
			m++;
		}
		t=array[k];array[k]=array[i];array[i]=t;
	}
	printf("%d\n",m);
}

void main(){
	int a[10]={3,5,8,9,18,29,14,10,20,25},i;
	printf("The primary array\n");
	for(i=0;i<10;i++){
		printf("%3d",a[i]);
	}
	sort(a,10);
	printf("\nThe sorted array\n");
	for(i=0;i<10;i++){
		printf("%3d",a[i]);
	}
}