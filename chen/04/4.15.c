#include<stdio.h>
#include<string.h>

char* fun(char* p1,char* p2){
	int i = 0;
	i = strcmp(p1,p2);
	if(0==i) return p1;
	else return p2;
}

//����ָ��ʹ��
void main(){
	char* p;
	char* (*pf)(char*,char*);//����ָ��
	char* (*pf1)(char*,char*);//����ָ��
	char* (*pf2)(char*,char*);//����ָ��
	//������ָ�븳ֵʱ������&fun��ֱ���ú�����fun.
	//��Ϊ������������֮����ʵ����һ����ַ
	pf = &fun;
	printf("pf = %s\n",(*pf)("aa","bb"));
	
	pf1 = fun;
	printf("pf1 = %s\n",(*pf1)("bb","cc"));
	printf("addr fun = %p,sizeof fun = %d",&fun,sizeof(fun));
	
	//*pf2 = &fun;//��ֵ���������������������ֵ
	//*pf2 = fun;//��ֵ���������������������ֵ
	//printf("pf2 = %s\n",(*pf2)("dd","dm"));
	
}