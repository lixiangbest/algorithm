#include<stdio.h>

//���ӷ���ֵ˵���ĺ���Ϊint����
add(int a,int b){
	return a+b;
}

//fun()�����������κβ���
fun(){//ǰ��void�����޷���ֵ�ĺ����У�return������ֵ
	return 1;
}

//fun1(void)�����������κβ���
fun1(void){//����ʱfun1(2)��ʾ��������ʵ��̫��
	return 2;
}

void main(){
	printf("2+3=%d\n",add(2,3));
	printf("%d %d\n",fun(2),fun1());
}