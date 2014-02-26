#include<stdio.h>

//a和&a的区别
void main(){
	int a[5] = {1,2,3,4,5};
	//&a + 1: 取数组a 的首地址，该地址的值加上sizeof(a) 的值，即&a + 5*sizeof(int)，也就是下一个数组的首地址，显然当前指针已经越过了数组的界限。
	int *ptr = (int*)(&a+1);//对指针加1操作，得到的是下一个元素的地址
	printf("*(a+1)=%d,*(ptr-1)=%d,*ptr=%d",*(a+1),*(ptr-1),*ptr);
}