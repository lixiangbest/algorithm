#include<stdio.h>

/*预处理命令：用函数指针变量调用函数*/
#if(0)
void main(){
	int max(int x,int y);
	int a=5,b=10;
	printf("a=%d,b=%d,max=%d\n",a,b,max(a,b));
}
#endif

#if(1)
void main(){
	int max(int x,int y);
	int (*p)();
	int a=5,b=10,c;
	p = max;
	c = (*p)(a,b);
	printf("a=%d,b=%d,max=%d",a,b,c);
}
#endif

int max(int x,int y){
	int z;
	if(x>y) z = x;
	else z = y;
	return z;
}
