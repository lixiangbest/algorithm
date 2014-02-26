#include<stdio.h>

void main(){
	//extern char a[]和extern char a[100]等价的原因是：
	//只是声明，不分配空间，所以编译器无需知道这个数组有多少个元素。
	extern char a[];//定义为数组，声明为指针
	//extern char a[50];//定义为数组，声明为指针
	//extern char* a;//定义为数组，声明为指针
	printf("%s\n",a);//Segmentation fault(core dumped)
	
	int ai[5] = {1,4,5,6,10};
	char ac[7] = "lixiang";
	printf("&ai[0]=%p,&ai[1]=%p,&ai[2]=%p\n",&ai[0],&ai[1],&ai[2]);
	printf("&ac[0]=%p,&ac[1]=%p,&ac[2]=%p",&ac[0],&ac[1],&ac[2]);
}