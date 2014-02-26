#include<stdio.h>

// 结构体占内存大小计算
void main(){
	struct A{
		int a;
		double b;
		char c;
	};
	struct B{
		double b;
		char c;
		int a;
	};
	struct C{
		int a;
		char c;
		double b;
	};
	struct A aa;
	struct B bb;
	struct C cc;
	printf("A=%d\n",sizeof(aa));//24
	printf("B=%d\n",sizeof(bb));//16
	printf("C=%d\n",sizeof(cc));//16
	/*
	32位系统
	int占4个字节，char占1个字节，double占8个字节
	
	struct A先给int a分配四个字节，并且以4个字节对齐；
	然后给double b分配8个字节，发现4个字节对齐不行，就以8个字节对齐
	前面只有int a，所以int a将占用8个字节；
	最后为了对齐，将给char c也分配8个字节，所以A占用24个字节
	
	struct B首先给double分配8个字节，并且以8给字节对齐；
	然后给char c分配8个字节；
	最后给int a分配空间时发现，前面空有7个字节空间可以放下int a，
	int a就和char c一起占用8个字节，所以结构体B占用了16个字节
	*/
}