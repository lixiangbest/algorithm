/**
 * �ʷ������塱
*/
#include<stdio.h>

void print(){
	printf("fp() is short of (*fp)()\n");
	printf("*fp()=*(fp()) is short of *((*fp)())\n\n");
}

void main(){
	//���������ǣ���������ֵʱ��((f))������Ϊ�������ͣ��ɴ˿���֪fҲ�Ǹ�������
	float ((f));
	//g��һ���������ú����ķ���ֵ����Ϊָ�򸡵�����ָ��
	//h��һ������ָ�룬h��ָ�����ķ���ֵΪ�������ͣ����(float(*)())��ʾ��ָ�򷵻�ֵΪ�������͵ĺ�����ָ�롱������ת����
	float *g(),(*h)();
	float fm;
	((f)) = 2.1;
	printf("((f)) = %f\n",((f)));
	fm = 2.1;
	f = 2.2;
	printf("fm = %f,f = %f\n",fm,f);
	
	//���ú���
	print();
	(*print)();
	
	//����ָ�򷵻�ֵΪvoid���͵ĺ�����ָ������
	typedef void (*funcptr)();
	(*(funcptr)print)();
	
	typedef void (*HANDLER)(int);
	HANDLER signal(int, HANDLER);
}
