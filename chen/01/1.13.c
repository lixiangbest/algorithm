#include<stdio.h>

//const���κ����Ĳ���
int func(const int i){//���߱�����i�ں������в��ܸı�
	//i = 5;//������ֻ��λ��'i'��ֵ
	return i;
}

//const���η���ֵ
const int func1(){
	return 15;
}

void main(){
	int const a[5] = {1,2,3,4,5};
	const int b[5] = {6,7,8,9,10};
	int i;
	//const int *p;//p�ɱ䣬pָ��Ķ��󲻿ɱ�
	//int const *p;//p�ɱ䣬pָ��Ķ��󲻿ɱ�
	//int *const p;//p���ɱ䣬pָ��Ķ���ɱ�
	//const int *const p;//p��pָ��Ķ��󶼲��ɱ�
	int *const p = &i;
	int m;
	printf("int const a:\n");
	for(i=0;i<5;i++){
		printf("%d ",a[i]);
	}
	printf("\nint const b:\n");
	for(i=0;i<5;i++){
		printf("%d ",b[i]);
	}
	//a[4] = 20;//������ֻ��λ��'a[4]'��ֵ
	printf("\n*p = %d",*p);
	printf("\ni = %d",func(i));
	
	m = func1();
	printf("\nm = %d",m);
	m = 17;
	printf("\nm = %d",m);
}