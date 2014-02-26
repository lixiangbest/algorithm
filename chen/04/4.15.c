#include<stdio.h>
#include<string.h>

char* fun(char* p1,char* p2){
	int i = 0;
	i = strcmp(p1,p2);
	if(0==i) return p1;
	else return p2;
}

//函数指针使用
void main(){
	char* p;
	char* (*pf)(char*,char*);//函数指针
	char* (*pf1)(char*,char*);//函数指针
	char* (*pf2)(char*,char*);//函数指针
	//给函数指针赋值时，可用&fun或直接用函数名fun.
	//因为函数名被编译之后其实就是一个地址
	pf = &fun;
	printf("pf = %s\n",(*pf)("aa","bb"));
	
	pf1 = fun;
	printf("pf1 = %s\n",(*pf1)("bb","cc"));
	printf("addr fun = %p,sizeof fun = %d",&fun,sizeof(fun));
	
	//*pf2 = &fun;//赋值运算的做操作数必须是左值
	//*pf2 = fun;//赋值运算的做操作数必须是左值
	//printf("pf2 = %s\n",(*pf2)("dd","dm"));
	
}