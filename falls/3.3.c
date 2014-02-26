/*
* * 作为参数的数组声明
*/
#include<stdio.h>
#include<string.h>

int main(){
	//C语言中，没有办法将一个数组作为函数参数直接传递。如果我们使用数组名作为参数，那么数组名会立刻被转换为指向数组第1个元素的指针。
	char hello[] = "hello";
	printf("%s\n", hello);
	printf("%s\n", &hello[0]);//因此，将数组作为函数参数毫无意义。所以C语言中会自动地将作为参数的数组声明转换为相应的指针声明。
	
	char *p,*q;//复制指针并不同时复制指针所指向的数据
	p = "xyz";//p是一个指向由'x','y','z'和'\0'的4个字符组成的数组的起始元素的指针。
	q = p;//p和q现在是两个指向内存中同一个地址的指针。这个赋值语句并没有同时复制内存中的字符。
	printf("p = %s,q = %s\n",p,q);
	q[1] = 'Y';
	printf("p = %s,q = %s\n",p,q);
	
	//当常数0被转换为指针使用时，这个指针绝对不能被解除引用(dereference)。
	//换句话说，当我们将0赋值给一个指针变量时，绝对不能企图使用该指针所指向的内存中存储的内容
	p = NULL;
	if(p==(char*)0) printf("0\n");//合法
	//非法的原因是strcmp库函数的实现中包括查看它的指针参数所指向内存中的内容的操作
	//if(strcmp(p, (char*)0)==0) printf("cmp\n");//不合法，编译通过，输出时报错：Segmentation fault(core dumped)
	//printf(p);
	printf("%s",p);
	
	return 0;
}
