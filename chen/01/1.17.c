#include<stdio.h>
#include<stdlib.h>

// ��������
void main(){
	int i;
	int a[0];
	typedef struct st_type{
		int i;
		//��ʹ����������ʱ��Ҫ���������ṹ���һ����Ա��
		//����������ʵ�ͽṹ��ûʲô��ϵ���㲻�ýṹ�����ʽ��Ա��
		//C99 a[0]Ҳ��
		int a[];//�ṹ�岻��������������ڴ��С����������ֻ�Ǳ�����Ա����ռ�ṹ��ı���
	}type_a;
	printf("sizeof int %d,\nsizeof flexible array:%d\n",sizeof i,sizeof(type_a));
	type_a *p = (type_a *)malloc(sizeof(type_a)+100*sizeof(int));
	printf("sizeof struct var after malloc:%d\n",sizeof(*p));
}