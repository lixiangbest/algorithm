#include<stdio.h>

void swap(int *p1,int *p2){
	int a,*temp=&a;
	//temp = &a;
	*temp = *p1;
	*p1 = *p2;
	*p2 = *temp;
	/*
	int temp;
	temp = *p1;//*temp = *p1 is error.Because the address of temp isn't sure.*temp is not sure.
	*p1 = *p2;
	*p2 = temp;
	*/
}

void main(){
	int a,b;
	int *pointer_1,*pointer_2;
	scanf("%d %d",&a,&b);
	pointer_1=&a;pointer_2=&b;
	if(a<b) swap(pointer_1,pointer_2);
	printf("\n%d,%d\n",*pointer_1,*pointer_2);
	printf("\n%d,%d\n",a,b);
}