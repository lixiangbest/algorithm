#include<stdio.h>

void main(){
	//寄存器变量的使用
	auto int i=1;
	register int r=i;
	register char *c = "Look";
	register float f = 2.15;
	register float a[3] = {1,2,3};
	f = 3.15;
	//错误，要求寄存器变量'r'的地址
	//printf("auto i = %d\nregister r = %d %d\n",i,r,&r);
	printf("auto i = %d\nregister r = %d\n",i,r);
	printf("register s = %s\nregister f = %f\n",c,f);
	printf("register arr = %f %f %f",a[0],a[1],a[2]);
}