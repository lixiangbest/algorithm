#include<stdio.h>

//��ַ��ǿ��ת��
void main(){
	int a[4] = {1,2,3,4};
	int* ptr1 = (int*)(&a+1);
	//��ǿ������ת��Ϊint�ټ�1
	//(int)a+1��ֵ��Ԫ��a[0]�ĵڶ����ֽڵĵ�ַ��Ȼ�����ǿ��ת��Ϊint*����
	//��ֵ����ptr2����*ptr2Ӧ��ΪԪ��a[0]�ĵڶ����ֽڿ�ʼ������4��byte������
	int* ptr2 = (int*)((int)a+1);//ָ��ָ���ָ��
	int* ptr3 = a+1;
	printf("%p,%p,%p,%p",ptr1[-2],ptr1[-1],*ptr2,*ptr3);
}