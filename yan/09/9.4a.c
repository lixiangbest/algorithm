/**
	ͨ�������ı�ָ��ָ���ֵ
	���ڣ�2012��7��30��
*/
#include<stdio.h>
#include<stdlib.h>

int m = 2, n = 3;
void change(int *p){
	int m;
	//*p = 4;//�ı�ָ��ָ���ֵ
	p = &n;//�ı�ָ���ָ�򣬶�ʵ����Ӱ��
}

//�ı�ָ��ָ���ָ�룬��ʹָ��ָ�������Ԫ��
void changeP(int **p){
	int m;
	*p = &n;//�ı�ָ��ָ���ָ��
}

void main(){
	int *pm = &m;
	printf("Before change:%d\n",*pm);
	change(pm);
	printf("After change:%d\n",*pm);
	changeP(&pm);
	printf("After changeP:%d\n",*pm);
}