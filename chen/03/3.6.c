#include<stdio.h>

//内存对齐问题和#pragma pack()
void main(){
	//编译器将按照n个字节对齐
	//#pragma pack(2)
	//编译器将取消自定义字节对齐方式
	//#pragma pack()
	struct TestStruct1{
		char c1;//第一个成员偏移量为0
		short s;//第二个成员偏移量等于第一个偏移量加第一个成员的大小0+1，根据原则1，偏移量必须是成员大小的整数倍，即偏移量必须是sizeof(short)的整数倍
		char c2;//
		int i;
	};
	/*
	结构体占内存大小计算：
	编译器编译程序时遵循两条原则：
	1、结构体变量中成员的偏移量必须是成员大小的整数倍(0是任何数的整数倍)
	2、结构体大小必须是所有成员大小的整数倍
	大家定义结构体类型时需要考虑到字节对齐的情况，不同顺序会影响到结构体的大小
	*/
	//避免内存对齐的影响，提供性能，节约空间
	struct TestStruct2{
		char c1;
		char c2;
		short s;
		int i;
	};
	int arr[3] = {2,3,4},*p = arr;
	int i = 16, j = -1;
	char c = 'a';
	printf("i = %p, c = %p, j = %p\n\n",i,c,j);
	
	printf("&arr:%d,arr:%d,*p:%d,&arr[1]:%d,&*(p+1):%d\n",&arr,arr,&*p,&arr[1],&*(p+1));
	printf("arr[0]:%d arr[1]:%d,arr[1]:%d\n",&arr[0]-arr,&arr[1]-&arr[0],&*(p+1)-&*p);
	printf("sizeof arr:%d,*p:%d\n\n",sizeof(arr),sizeof(*p));
	
	struct TestStruct1 a;
	a.c1 = 'a';a.s = 3;a.i = 120;
	struct TestStruct2 b;
	printf("struct a:%d,struct b:%d\n",sizeof(a),sizeof(b));//12,8
	//计算地址的偏移量，单位为1byte.
	printf("sizeof char:%d, struct char c1:%d\n",sizeof(char),sizeof(a.c1));
	printf("sizeof short:%d, struct short s:%d\n",sizeof(short),sizeof(a.s));
	printf("sizeof char:%d, struct char c2:%d\n",sizeof(char),sizeof(a.c2));
	printf("sizeof int:%d, struct int i:%d\n",sizeof(int),sizeof(a.i));
	
	//缺省情况下，编译器默认将结构、栈中的成员数据进行内存对齐
	//编译器将未对气的成员向后移，将每个的成员对齐到自然边界上，
	//从而导致了整个结果的尺寸变动。尽管会牺牲一点空间(成员之间有部分内存空闲)
	//但提高了性能
	printf("\na %p,c1 %p,s %p,c2 %p,i %p\n",
		(unsigned int)(void*)&a,
		(unsigned int)(void*)&a.c1-(unsigned int)(void*)&a,
		(unsigned int)(void*)&a.s-(unsigned int)(void*)&a,
		(unsigned int)(void*)&a.c2-(unsigned int)(void*)&a,
		(unsigned int)(void*)&a.i-(unsigned int)(void*)&a
	);
	
	printf("\nb %p,c1 %p,s %p,c2 %p,i %p\n",
		(unsigned int)(void*)&b,
		(unsigned int)(void*)&b.c1-(unsigned int)(void*)&b,
		(unsigned int)(void*)&b.s-(unsigned int)(void*)&b,
		(unsigned int)(void*)&b.c2-(unsigned int)(void*)&b,
		(unsigned int)(void*)&b.i-(unsigned int)(void*)&b
	);
	
	printf("\na.c1=%c,a.s=%d,a.i=%d\n",a.c1,a.s,a.i);
	
}