#include<stdio.h>

void main(){
	//�Ĵ���������ʹ��
	auto int i=1;
	register int r=i;
	register char *c = "Look";
	register float f = 2.15;
	register float a[3] = {1,2,3};
	f = 3.15;
	//����Ҫ��Ĵ�������'r'�ĵ�ַ
	//printf("auto i = %d\nregister r = %d %d\n",i,r,&r);
	printf("auto i = %d\nregister r = %d\n",i,r);
	printf("register s = %s\nregister f = %f\n",c,f);
	printf("register arr = %f %f %f",a[0],a[1],a[2]);
}