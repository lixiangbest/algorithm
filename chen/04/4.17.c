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

//函数指针数组
void main(){
	char*(*pf[3])(char*p);
	pf[0] = fun1;//可直接用函数名
	pf[1] = &fun2;//可用函数名加上取地址符
	pf[2] = &fun3;
	
	(*pf[0])("fun1");//运算符的优先级
	pf[1]("fun2");
	pf[2]("fun3");
}