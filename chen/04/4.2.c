#include<stdio.h>

#define Address 0x22cc88

void main(){
	int i = 10;
	int *p = (int*)Address;
	printf("&i = %p\n",&i);
	printf("p = %p,*p = %d\n",p,*p);
	*p = 0x100;
	printf("*p = %d\n",*p);
	//����ֵ�洢��ָ�����ڴ��ַ
	*(int*)Address = 0x100;
	printf("Address = %d\n",*(int*)Address);
}