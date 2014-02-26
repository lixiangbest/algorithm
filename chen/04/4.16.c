#include<stdio.h>

void Function(){
	printf("Call Function!\n");
}

//*(int*)&p--这是什么？
void main(){
	//这行代码定义了一个指针变量p
	//p指向一个函数，这个函数的参数和返回值都是void
	void (*p)();
	//&p求指针变量p本身的地址，一个32位的二进制常数
	//(int*)&p表示将地址强制转换为指向int类型数据的指针
	//(int)Function表示将函数入口地址强制转换为int类型的数据
	*(int*)&p = (int)Function;
	(*p)();
	
	int i = 3;
	int*p1,*p2;//p2前加*，不然被认为是int变量，而不是指针变量
	p1 = &i;
	p2 = &i;
	printf("%p,%p\n",*p1,*p2);
	*(int*)&p2 = (int)&i;
	printf("%p",*p2);
}