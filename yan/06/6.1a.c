#include<stdio.h>

/*指针数组与数组指针*/
void main(){
	int c[4] = {1,2,3,4};
	int i;
	int *a[4];//指针数组
	int (*b)[4];//数组指针
	int m = c;//指针，但不是数组指针，指针和数组指针主要不同是自增移动的字节大小不同
	//int *d = a;
	b = &c;//注意这里不能是c，否则从不兼容的指针类型初始化
	//将数组c中元素赋给数组a
	printf("Array c:\n");
	for(i=0;i<4;i++){
		a[i] = &c[i];
		printf("%-3d ",*a[i]);
	}
	//b++;//这里不能自增，自增+1会使b移动4*2个字节
	printf("\nB++ Move %d %d bytes\n", b+1, b);
	printf("\nA++ Move %d %d bytes\n", a+1, a);
	//数组输出
	printf("\n*a[1] = %d\n(*b)[2]=%d",*a[1],(*b)[2]);
	//d++;
	//b++;
	//printf("\n*a[1] = %d\n(*b)[2]=%d",*d,(*b)[2]);
}