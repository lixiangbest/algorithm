#include<stdio.h>

int fun1(void){
	static int i=0;
	i++;
	return i;
}

void fun2(void){
	extern j;//声明全局变量
	//j = 0;//可以注释掉
	j++;
}

static int h;//定义静态全局变量

void fun3(void){
	h=0;
	h++;
}

int j;//定义全局变量

int g;//定义全局变量

void main(){
	//static关键字的用法，全局变量的定义
	int k,m;//i是静态局部变量
	printf("global g=%d\n",g);
	for(k=0;k<10;k++){
		m = fun1();
		fun2();
		fun3();
	}
	printf("i=%d j=%d h=%d\n",m,j,h);
}