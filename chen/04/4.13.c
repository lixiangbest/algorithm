#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//һ��ָ�����
void fun(char *p){
	char c = p[3];//������char c = *(p+3)
	printf("%c\n",c);
}

//��������ʱ���õ��Ķ���p2�Ŀ���_p2����p2����
void getMemory(char *p,int num){
	//malloc���ڴ�ĵ�ַ��û�и���str�����Ǹ�����_str(str�Ŀ���)
	//���_str�Ǳ������Զ�����ͻ��յģ����Ǹ����޷�ʹ�ã����ȡһ���ڴ��ǲ��е�
	p = (char*)malloc(num*sizeof(char));
	printf("sizeof(p)=%d,sizeof(*p)=%d",sizeof(p),sizeof(*p));
}

void main(){
	//main�����ڵı�������ȫ�ֱ��������Ǿֲ�����
	//ֻ���������������ں�ȫ�ֱ���һ�������ѣ�ȫ�ֱ���һ���Ƕ����ں����ⲿ��
	char *p2 = "abcdefg";
	fun(p2);
	
	//�޷���ָ����������ݸ�һ������
	char *str = NULL;
	getMemory(str,10);
	//strcpy(str,"hello");//segmentation fault(core dumped)
	printf("\n%p\n",str);//0
	free(str);//free��û�������ã��ڴ�й¶
}