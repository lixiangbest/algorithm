#include<stdio.h>

extern int i;//���ﲻ�ܳ�ʼ��д��i=10�����򱨴�i�ѳ�ʼ����ȴ������Ϊ'extern'
extern void fun(void);//����void����ʡ��

//extern�ؼ��ֵ�ʹ��
void main(){
	i = 15;
	printf("i = %d",i);
	fun();
	
	extern double j;//����
	j = 3.0;//����
	printf("\n%f",j);
	printf("\n%d",j);
}