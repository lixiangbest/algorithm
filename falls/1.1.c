/*
P18 �ʷ������е�̰�ķ�
P21 ʮ����д�ɰ˽���
*/
#include<stdio.h>

int main(){
	int a = 7;
	int *b = &a;
	a = a / *b;
	printf("a=%d\n",a);
	
	//���ͳ���
	printf("046 = %d\n",046);//�˽���
	printf("46 = %d\n",46);//ʮ����
	
	//��������˫���Ż���
	//char *slash = '/';//���棺��ʼ��ʱ����������ָ�룬δ������ת��
	//printf('\n');//���棺���ݸ���printf���ĵ�1������ʱ����������ָ�룬δ������ת����printf��Ҫ����'const char *'����ʵ�ε�����Ϊ'int'

	//�������Ĵ洢�ռ�����ɶ���ַ����е�c������������һ���ַ������а�������ַ�
	//char y = 'yes';//���棺���ֽ��ַ���������ʽ����ת�����
	//printf("y = '%c'\n",y);
	char *m = "yes";
	printf("m = '%c'\n",*m);
	
	//Ƕ��ע��
	char *n = /*/**/"*/"/*"/**/;
	printf("n = %s\n",n);
	
	//n-->0
	printf("n-->0:%d\n",a--<=0);
	
	a = 1;
	int c = 1;
	//a+++++b:((a++)++)+b//����������������������ֵ
	//printf("a+++++b:%d\n",a+++++c);
	
	return 0;
}