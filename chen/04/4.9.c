#include<stdio.h>

//地址的强制转换
void main(){
	int a[4] = {1,2,3,4};
	int* ptr1 = (int*)(&a+1);
	//先强制类型转换为int再加1
	//(int)a+1的值是元素a[0]的第二个字节的地址，然后把它强制转换为int*类型
	//的值赋给ptr2，即*ptr2应该为元素a[0]的第二个字节开始的连续4个byte的内容
	int* ptr2 = (int*)((int)a+1);//指向指针的指针
	int* ptr3 = a+1;
	printf("%p,%p,%p,%p",ptr1[-2],ptr1[-1],*ptr2,*ptr3);
}