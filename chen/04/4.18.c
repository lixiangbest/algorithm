#include<stdio.h>
#include<string.h>

char* fun1(char* p){
	printf("%s\n",p);
	return p;
}

char* fun2(char* p){
	printf("%s\n",p);
	return p;
}

char* fun3(char* p){
	printf("%s\n",p);
	return p;
}

//函数指针数组的指针
void main(){
	//这里a并非指针，而是一个数组名
	char*(*a[3])(char*p);
	//这里pf是指针，指向一个包含3个元素的数组；这个数字里面存的是指向函数的指针
	//这些指针指向一些返回值类型为指向字符的指针，参数为一个指向字符的指针的函数
	char*(*(*pf)[3])(char*p);
	pf = &a;
	
	a[0] = fun1;
	a[1] = &fun2;
	a[2] = &fun3;
	
	pf[0][0]("fun1");
	pf[0][1]("fun2");
	pf[0][2]("fun3");
	
	printf("\n");
	
	(*(*pf))("fun1");
	(*(*pf+1))("fun2");
	(*(*pf+2))("fun3");
}