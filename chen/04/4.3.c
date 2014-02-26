#include<stdio.h>

int checkCPU(){
	union w{
		int a;
		char b;
	}c;
	c.a = 1;
	return(c.b==1);
}

void main(){
	int *p = (int*)0x22cc88;
	*p = NULL;
	printf("p = %p\n",p);
	
	//判断大端小端
	int i=1;
	char *pm = (char*)&i;
	if(*pm==1){
		printf("1\n");//小端模式
	}else printf("2\n");//大端模式
	
	/*				  数值来说1是高位，4是地位
	如果将一个16位的整数0x1234存放到一个短整型变量（short）中。这个短整型变量在内存中的存储在大小端模式由下表所示。
	地址偏移			大端模式	小端模式
	(低地址)0x00		12（OP0）	34（OP1）
	(高地址)0x01		34（OP1）	12（OP0）
	//由上表所知，采用大小模式对数据进行存放的主要区别在于在存放的字节顺序，大端方式将高位存放在低地址，小端方式将低位存放在低地址。
	采用大端方式进行数据存放符合人类的正常思维，而采用小端方式进行数据存放利于计算机处理。
	*/
	//请写一个C函数，若处理器是Big_endian的，则返回0；若是Little_endian的，则返回1
	printf("%d\n",checkCPU());//小端模式
}