#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//一级指针参数
void fun(char *p){
	char c = p[3];//或者是char c = *(p+3)
	printf("%c\n",c);
}

//函数运行时，用到的都是p2的拷贝_p2而非p2本身
void getMemory(char *p,int num){
	//malloc的内存的地址并没有赋给str，而是赋给了_str(str的拷贝)
	//这个_str是编译器自动分配和回收的，我们根本无法使用，想获取一块内存是不行的
	p = (char*)malloc(num*sizeof(char));
	printf("sizeof(p)=%d,sizeof(*p)=%d",sizeof(p),sizeof(*p));
}

void main(){
	//main函数内的变量不是全局变量，而是局部变量
	//只不过它的生命周期和全局变量一样长而已，全局变量一定是定义在函数外部的
	char *p2 = "abcdefg";
	fun(p2);
	
	//无法把指针变量本身传递给一个函数
	char *str = NULL;
	getMemory(str,10);
	//strcpy(str,"hello");//segmentation fault(core dumped)
	printf("\n%p\n",str);//0
	free(str);//free并没有起作用，内存泄露
}