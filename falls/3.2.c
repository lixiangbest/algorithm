/*
* 非数组的指针
*/
#include<stdio.h>

void main(){
	char calendar[12][31];//声明了calendar是一个数组，该数组拥有12个数组类型的元素，其中每个元素都是一个拥有31个整型元素的数组。(而不是一个拥有31个数组类型的元素的数组，其中每个元素又是一个拥有12个整型元素的数组。)
	printf("sizeof calendar = %d\n",sizeof(calendar));
	//如果calendar不是使用与calendar总是被转换成一个指向calendar数组的起始元素的指针。
	
	//calendar[4]的行为也就表现为一个有着31个整型元素的数组的行为
	printf("sizeof calendar[4] = %d\n",sizeof calendar[4]);
	printf("sizeof calendar[5] = %d\n",sizeof calendar[5]);
	
	//calendar[4]
	char *p = calendar[4];//p指向数组calendar[4]中下标为0的元素
	printf("sizeof *p = %d, sizeof p = %d\n",sizeof *p,sizeof p);
	
	//p = calendar;//警告：从不兼容的指针类型赋值。calendar是一个二维数组，即“数组的数组”。这里将calendar转换为一个指向数组的指针；而p是一个指向整型变量的指针。
	
	char (*monthp)[31];//声明了*monthp是一个拥有31个字符类型元素的数组，monthp就是一个指向这样的数组的指针。
	monthp = calendar;//monthp指向数组calendar的第1个元素，也就是数组calendar的12个有着31个元素的数组类型元素之一。
}