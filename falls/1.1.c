/*
P18 词法分析中的贪心法
P21 十进制写成八进制
*/
#include<stdio.h>

int main(){
	int a = 7;
	int *b = &a;
	a = a / *b;
	printf("a=%d\n",a);
	
	//整型常量
	printf("046 = %d\n",046);//八进制
	printf("46 = %d\n",46);//十进制
	
	//单引号与双引号混用
	//char *slash = '/';//警告：初始化时将整数赋给指针，未作类型转换
	//printf('\n');//警告：传递给‘printf’的第1个参数时将整数赋给指针，未作类型转换，printf需要类型'const char *'，但实参的类型为'int'

	//整型数的存储空间可容纳多个字符，有的c编译器允许在一个字符常量中包含多个字符
	//char y = 'yes';//警告：多字节字符常量，隐式常量转换溢出
	//printf("y = '%c'\n",y);
	char *m = "yes";
	printf("m = '%c'\n",*m);
	
	//嵌套注释
	char *n = /*/**/"*/"/*"/**/;
	printf("n = %s\n",n);
	
	//n-->0
	printf("n-->0:%d\n",a--<=0);
	
	a = 1;
	int c = 1;
	//a+++++b:((a++)++)+b//错误：自增操作数必须是左值
	//printf("a+++++b:%d\n",a+++++c);
	
	return 0;
}