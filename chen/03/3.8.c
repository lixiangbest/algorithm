#include<stdio.h>

void main(){
	//指定对齐参数为8
	#pragma pack(8)
	struct TestStruct4{
		char a;
		long b;
	};
	/*
	TestStruct4中，成员a是1字节默认按1字节对齐，指定对齐参数为8，
	这两个值取1，a按1字节对齐；成员b是4个字节，默认是按4字节对齐，这时就按
	4字节对齐。sizeof(TestStruct4)应该为8
	*/
	struct TestStruct5{
		char c;
		struct TestStruct4 d;
		long long e;//8个字节
	};
	/*
	TestStruct5中，c和TestStruct4中的a一样，按1字节对齐，而d是个结构，它是8个字节，
	而对于结构来说，它的默认对齐方式是它的所有成员使用的对齐参数中最大的一个。
	TestStruct4是4，所有成员d就按4字节对齐。成员e是8个字节，它是默认按8个字节对其的，
	和指定的一样，所以它对到8个字节的边界上，这是，已经使用了12个字节了(char c效仿d按4字节对齐)，所以又添加了4个字节的空，从第16个字节开始放置成员e。这时，
	长度为24，已经可以被8（成员e按8字节对齐）整除。
	*/
	printf("sizeof long long:%d\n",sizeof(long long));
	printf("sizeof TestStruct4:%d\n",sizeof(struct TestStruct4));//8
	printf("sizeof TestStruct5:%d\n",sizeof(struct TestStruct5));//24
	#pragma pack()
	printf("\nsizeof TestStruct4:%d\n",sizeof(struct TestStruct4));
	printf("sizeof TestStruct5:%d\n",sizeof(struct TestStruct5));
}