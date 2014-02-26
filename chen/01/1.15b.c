#include<stdio.h>

extern int i;//这里不能初始化写成i=10，否则报错：i已初始化，却被声明为'extern'
extern void fun(void);//两个void可以省略

//extern关键字的使用
void main(){
	i = 15;
	printf("i = %d",i);
	fun();
	
	extern double j;//可以
	j = 3.0;//可以
	printf("\n%f",j);
	printf("\n%d",j);
}