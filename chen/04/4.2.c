#include<stdio.h>

#define Address 0x22cc88

void main(){
	int i = 10;
	int *p = (int*)Address;
	printf("&i = %p\n",&i);
	printf("p = %p,*p = %d\n",p,*p);
	*p = 0x100;
	printf("*p = %d\n",*p);
	//将数值存储到指定的内存地址
	*(int*)Address = 0x100;
	printf("Address = %d\n",*(int*)Address);
}