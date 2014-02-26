#include<stdio.h>
#include "4.1.h"

main(){
	//外部变量引用
	printf("%s",filename);
	
	//extern int sqrt();//隐式声明
	printf("%g\n",sqrt(2));//警告：隐式声明与内建函数'sqrt'不兼容
}