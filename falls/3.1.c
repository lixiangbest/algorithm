/*
* 语义 “陷阱”
*/
#include<stdio.h>

struct{
	int p[4];
	double x;
}b[17];
//b是一个拥有17个元素的数组，其中每个元素都是一个结构，该结构中包括了一个拥有4个整型元素的数组(命名为p)和一个双精度类型的变量(命名为x)

int main(){
	int b = 1;
	printf("b=%d\n",b);
	
	int calendar[12][31];//声明了calendar是一个数组，该数组拥有12个数组类型的元素，其中每个元素都是一个拥有31个整型元素的数组。(而不是一个拥有31个数组类型的元素的数组，其中每个元素又是一个拥有12个整型元素的数组。)
	printf("sizeof = %d\n",sizeof(calendar));
	//如果calendar不是使用与calendar总是被转换成一个指向calendar数组的起始元素的指针。
	
	int a[3];
	int *p = a;//这里如果我们在应该出现指针的地方，却采用了数组名来替换，那么数组名就被当做指向该数组下标为0的元素指针。这样会把数组a中下标为0的元素的地址赋值给p。
	//而如果写成p = &a则警告：从不兼容的指针类型初始化。因为&a是一个指向数组的指针，p是一个指向整型变量的指针。
	//p指向数组a中下标为0的元素，p+1指向数组a中下标为1的元素，p+2指向数组a中下标为2的元素。
	printf("sizeof(a) = %d,sizeof(int) = %d\n",sizeof a,sizeof(int));//除了a被用作运算符sizeof的参数这一情形，在其他所有的情形中数组名a都代表指向数组a中下标为0的元素的指针。而sizeof(a)的结果是整个数组a的大小
	*a = 84;//*a即数组a中下标为0的元素的引用
	printf("a[0] = %d,*a = %d,*(a+0) = %d,*(0+a) = %d,0[a] = %d\n",a[0],*a,*(a+0),*(0+a),0[a]);
	return 0;
}