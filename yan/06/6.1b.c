#include<stdio.h>

/*函数指针*/
void main(){
	int max(int,int);
	int (*p)(int,int);
	//一个函数在编译时被分配给一个入口地址，这个函数的入口地址就成为函数的指针
	//此处利用p=max是正确的指向函数的指针的用法，p指向max的入口地址
	//所以在执行(*p)(q,w)它时其实是执行的(max)(q,w)
	p = max;
	
	//此处用*p=max得到相同结论，因为这样赋值之后*p的内容就是max
	//所以在执行(*p)(q,w)它时其实是执行的(max)(q,w)
	//*p = max;//gcc下面貌似不行啊
	int q=8,w=12;
	printf("The larger number is:%d\n",(*p)(q,w));
	printf("The larger number is:%d\n",(*p)(w,q));
}

int max(int a, int b){
	if(a>b) return a;
	else return b;
}