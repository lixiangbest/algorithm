#include<stdio.h>

/*�ú���ָ�������Ϊ�������ݸ���������*/
void main(){
	int a,b;
	int min(int,int);/*��������*/
	int max(int,int);/*��������*/
	int sum(int,int);/*��������*/
	void process(int x,int y,int(*fun)());//��������
	a = 5,b = 8;
	printf("a=%d,b=%d\n",a,b);
	printf("max=");
	process(a,b,max);
	printf("min=");
	process(a,b,min);
	printf("sum=");
	process(a,b,sum);
}

/*����Сֵ����*/
int min(int x,int y){
	int z;
	if(x>y) z = y;
	else z = x;
	return z;
}

/*�����ֵ����*/
int max(int x,int y){
	return (x>y)?x:y;
}

/*��ͺ���*/
int sum(int x,int y){
	return x+y;
}

void process(int x,int y,int (*fun)()){//����Ҳ����ָ������(*fun)(int,int)
	int result;
	result = (*fun)(x,y);
	printf("%d\n",result);
}