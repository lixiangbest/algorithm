#include<stdio.h>

/*����ָ��*/
void main(){
	int max(int,int);
	int (*p)(int,int);
	//һ�������ڱ���ʱ�������һ����ڵ�ַ�������������ڵ�ַ�ͳ�Ϊ������ָ��
	//�˴�����p=max����ȷ��ָ������ָ����÷���pָ��max����ڵ�ַ
	//������ִ��(*p)(q,w)��ʱ��ʵ��ִ�е�(max)(q,w)
	p = max;
	
	//�˴���*p=max�õ���ͬ���ۣ���Ϊ������ֵ֮��*p�����ݾ���max
	//������ִ��(*p)(q,w)��ʱ��ʵ��ִ�е�(max)(q,w)
	//*p = max;//gcc����ò�Ʋ��а�
	int q=8,w=12;
	printf("The larger number is:%d\n",(*p)(q,w));
	printf("The larger number is:%d\n",(*p)(w,q));
}

int max(int a, int b){
	if(a>b) return a;
	else return b;
}