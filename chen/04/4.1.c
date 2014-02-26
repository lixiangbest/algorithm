#include<stdio.h>

//指针的内存布局
//指针变量p里存储的内存地址处的内存称为p所指向的内存
//p里存储的任何数据都将被当作地址来处理
//32位系统下，不管什么样的指针类型，其大小都为4byte

//"*"与防盗门的钥匙
void main(){
	int *p1;
	printf("sizeof(p1)=%d,sizeof(int*)=%d,sizeof(void*)=%d,sizeof(void)=%d",sizeof(p1),sizeof(int*),sizeof(void*),sizeof(void));
	
	printf("\naddress p1 = %d,%x,%p",p1,p1,p1);
	/*定义一个指针变量pn，其指向的内存里面保存的是int类型的数据
	定义变量p的同时把pn的值设置为0x00000000，而不是把*pn的值设置为0x00000000
	该过程叫做初始化，在编译时进行
	*/
	int *pn = NULL;
	printf("\naddress pn = %d,%x,%p",pn,pn,pn);
	
	/*定义一个指针变量pm，其指向的内存里面保存的是int类型的数据
	这时候变量pm本身的值是多少不得而知，也就是说现在变量p保存的有可能
	是一个非法的地址。
	*/
	int *pm;
	/*给*p赋值NULL，即给p指向的内存赋值为NULL
	由于p指向的内存可能是非法的，所以调试时编译器可能会报告一个内存访问错误。
	*/
	//*pm = NULL;//警告：赋值时将指针赋给整数，未作类型转换
	//printf("\naddress p = %p,*p = %d",pm,*pm);
	
	int i = 10;
	int *pt = &i;
	*pt = NULL;//警告：赋值时将指针赋给整数，未作类型转换
	printf("\naddress pt = %p,*pt = %d",pt,*pt);
}