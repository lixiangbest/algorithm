#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//��return
char* getMemory1(char*p,int num){
	p = (char*)malloc(num*sizeof(char));
	return p;
}

//�ö���ָ��
void getMemory2(char **p,int num){
	*p = (char*)malloc(num*sizeof(char));
	return p;
}

//��ȡ��������ڴ�
void main(){
	char* str1 = NULL;
	char* str2 = NULL;
	str1 = getMemory1(str1,10);//��ֵ��str1�洢�����ڴ��ֵַ
	strcpy(str1,"Hello");
	printf("%s\n",str1);
	free(str1);
	printf("%p,%p\n",str1,*str1);
	
	//�ö���ָ��
	getMemory2(&str2,10);//���ݵ���str�ĵ�ַ����һ��ֵ��
	strcpy(str2,"Hello");
	printf("\n%s\n",str2);
	free(str2);
	printf("%p,%p",str2,*str2);
}