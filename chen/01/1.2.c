#include<stdio.h>

int fun1(void){
	static int i=0;
	i++;
	return i;
}

void fun2(void){
	extern j;//����ȫ�ֱ���
	//j = 0;//����ע�͵�
	j++;
}

static int h;//���徲̬ȫ�ֱ���

void fun3(void){
	h=0;
	h++;
}

int j;//����ȫ�ֱ���

int g;//����ȫ�ֱ���

void main(){
	//static�ؼ��ֵ��÷���ȫ�ֱ����Ķ���
	int k,m;//i�Ǿ�̬�ֲ�����
	printf("global g=%d\n",g);
	for(k=0;k<10;k++){
		m = fun1();
		fun2();
		fun3();
	}
	printf("i=%d j=%d h=%d\n",m,j,h);
}