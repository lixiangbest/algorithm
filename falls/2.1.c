/**
 * 词法“陷阱”
*/
#include<stdio.h>

void print(){
	printf("fp() is short of (*fp)()\n");
	printf("*fp()=*(fp()) is short of *((*fp)())\n\n");
}

void main(){
	//声明含义是：当对其求值时，((f))的类型为浮点类型，由此可推知f也是浮点类型
	float ((f));
	//g是一个函数，该函数的返回值类型为指向浮点数的指针
	//h是一个函数指针，h所指向函数的返回值为浮点类型，因此(float(*)())表示“指向返回值为浮点类型的函数的指针”的类型转换符
	float *g(),(*h)();
	float fm;
	((f)) = 2.1;
	printf("((f)) = %f\n",((f)));
	fm = 2.1;
	f = 2.2;
	printf("fm = %f,f = %f\n",fm,f);
	
	//调用函数
	print();
	(*print)();
	
	//定义指向返回值为void类型的函数的指针类型
	typedef void (*funcptr)();
	(*(funcptr)print)();
	
	typedef void (*HANDLER)(int);
	HANDLER signal(int, HANDLER);
}
