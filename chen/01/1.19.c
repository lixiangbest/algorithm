#include<stdio.h>

/* union�ؼ����÷�
  union ά���㹻�Ŀռ����÷Ŷ�����ݳ�Ա�еġ�һ�֡���������Ϊÿһ�����ݳ�Ա����
�ռ䣬��union �����е����ݳ�Ա����һ���ռ䣬ͬһʱ��ֻ�ܴ�������һ�����ݳ�Ա����
�е����ݳ�Ա������ͬ����ʼ��ַ��
*/

int checkSystem(){
	union check{
		int i;
		char ch;
	}c;
	c.i = 1;
	return c.ch==1;
}

void main(){
	int a[5] = {1,2,3,4,5};
	int *ptr1 = (int*)(&a+1);
	int *ptr2 = (int*)((int)a+1);
	int *i = a;
	int (*j)[] = &a+1;
	printf("a=%d,i=%d,j=%d\n",(int)a,i,j);
	printf("%d,%d,%d\n",ptr1[-2],ptr1[-1],ptr1[0]);
	printf("%x,%x,%x\n",ptr1[-1],*ptr2,*ptr1);
	printf("%d",checkSystem());
}