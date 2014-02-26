#include<stdio.h>
#define Total 5

void main(){
	int *p,i,a[Total];
	p = a;
	for(i=0;i<Total;i++){
		scanf("%d",p++);
	}
	printf("\n");//now p pointer to the end of array a,a[10]
	p=a;//now set p pointer to the start of array a,a[0]
	for(i=0;i<Total;i++){
		printf("%d ",*p++);
	}
	printf("\n");
	p=a;
	for(i=0;i<Total;i++){
		printf("%d ",*(++p));
	}
	printf("\n");
	p=a;
	for(i=0;i<Total;i++){
		(*p)++;
		printf("%d ",*p++);
	}
}