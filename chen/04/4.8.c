#include<stdio.h>

//��ַ��ǿ��ת��
void main(){
	struct Test{
		int Num;
		char *pcName;
		short sDate;
		char cha[2];
		short sBa[4];
	}*p;
	printf("sizeof(*p) = %d,*p = %d\n",sizeof(*p),*p);
	printf("%p %p %p\n",p,p+1,p+0x1);
	//�κ���ֵһ����ǿ��ת���������;͸ı���
	printf("%p %p %p\n",(unsigned long)p,(unsigned long)p+1,(unsigned long)p+0x1);
	printf("%p %p %p\n",(unsigned long*)p,(unsigned long*)p+1,(unsigned long*)p+0x1);
}