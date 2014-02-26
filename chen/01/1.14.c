#include<stdio.h>

//易变关键字-volatile的使用
void main(){
	int i = 10;
	int j = i;//(1)语句
	int k = i;//(2)语句
	//(1)、(2)语句中i没有被用作左值
	//编译器认为i的值没有发生改变
	printf("i = %d,j = %d,k = %d\n",i,j,k);
	
	volatile int m = 12;
	int n = m;
	int o = m;
	//volatile关键字告诉编译器m是随时可能发生变化的
	//每次使用它时必须从内存中取出i的值，因而编译器生成的
	//汇编代码会重新从m的地址处读取数据放在o中
	printf("m = %d,n = %d,o = %d\n",m,n,o);
	//如果i是一个寄存器变量或者表示一个端口数据或者是多个线程的共享数据，
	//就容易出错，所以说volatile可以保证对特殊地址的稳定访问
}