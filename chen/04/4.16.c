#include<stdio.h>

void Function(){
	printf("Call Function!\n");
}

//*(int*)&p--����ʲô��
void main(){
	//���д��붨����һ��ָ�����p
	//pָ��һ����������������Ĳ����ͷ���ֵ����void
	void (*p)();
	//&p��ָ�����p����ĵ�ַ��һ��32λ�Ķ����Ƴ���
	//(int*)&p��ʾ����ַǿ��ת��Ϊָ��int�������ݵ�ָ��
	//(int)Function��ʾ��������ڵ�ַǿ��ת��Ϊint���͵�����
	*(int*)&p = (int)Function;
	(*p)();
	
	int i = 3;
	int*p1,*p2;//p2ǰ��*����Ȼ����Ϊ��int������������ָ�����
	p1 = &i;
	p2 = &i;
	printf("%p,%p\n",*p1,*p2);
	*(int*)&p2 = (int)&i;
	printf("%p",*p2);
}