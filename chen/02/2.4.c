#include<stdio.h>


void main(){
	int i = 0;
	int j = 0;
	//逻辑运算符
	if((++i)>0||(++j>0)){
		printf("i=%d,j=%d",i,j);
	}
	
	//位运算符，左移和右移
	//+号的优先级比移位运算符的优先级高
	j = 0x01<<2+3;
	printf("\n0x01<<2+3:%d\n",j);
	
	//左移和右移的位数不能大于数据的长度，不能小于0
	//i = 0x01<<2+30;//左移次数大于或等于类型宽度
	//printf("\n0x01<<2+3:%d\n",i);//溢出
	//j = 0x01<<2-3;//左移次数为负
	//printf("\n0x01<<2-3:%d\n",j);
	
	// 花括号把一些语句或代码打包，使之形成一个整体，并与外界绝缘
	char a[10] = {"abcde"};
	//char b[10]{="abcde"};
}