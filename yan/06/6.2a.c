#include<stdio.h>

void main(){
	int a;
	printf("input the data\n");
	scanf("%d ",&a);//这里多了一个空格符12 12
	printf("%d",a);//要输入两个数程序才结束
	//原因：用空白符结尾时，scanf会跳过空白符去读下一个字符，所以你必须再输入一个 数。这里的空白符包括空格，制表符，换行符，回车符和换页符。所以如果你用scanf("%d  ",&a)也会出现同样的问题。
}