//#include�ǽ��Ѵ����ļ�������Ƕ�뵽��ǰ�ļ���
//include֧�����·������ʽ.����ǰĿ¼��..�����ϲ�Ŀ¼
#include"stdio.h"
#include<stdio.h>
//#include"./3.3.c"

// ��������
// #errorԤ����
// #lineԤ����
void main(){
	int i = 5;
	printf("i = %d\n",i);
	
	// #line�������Ǹı䵱ǰ�������ļ����ƣ��������ڱ��������Ԥ�ȶ���ı�ʶ��
	// ����
	#line 30
	
	//#errorԤ����ָ���������ڱ������ʱ��ֻҪ����#error�ͻ�����һ���������
	//��ʾ��Ϣ����ֹͣ����
	#error var i is not declared.
	#error "var i is not declared."
	printf("i = %d",i);
}