#include<stdio.h>

//无法向函数传递一个数组
//当一维数组作为函数参数时，编译器总是把它解析成一个指向其首元素首地址的指针
//实际传递的数组大小与函数形参指定的数组大小没有关系
//函数本身是没有类型的，只有函数的返回值才有类型的。
void fun(char a[10]){
	char c = a[3];
	int i = sizeof(a);//a为指针
	a = a+3;
	printf("sizeof a:%d,a[3] = %c,*(a+3) = %c\n",i,c,*a);
}

//数组参数和指针参数
void main(){
	char b[10] = "abcdefg";
	//需要类型'char*'，但实参的类型为char
	//fun(b[10]);//warning:传递'fun'的第1个参数时将整数赋给指针，未作类型转换
	fun(b);
}