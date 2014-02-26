#include<stdio.h>

//地址的强制转换
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
	//任何数值一旦被强制转换，其类型就改变了
	printf("%p %p %p\n",(unsigned long)p,(unsigned long)p+1,(unsigned long)p+0x1);
	printf("%p %p %p\n",(unsigned long*)p,(unsigned long*)p+1,(unsigned long*)p+0x1);
}