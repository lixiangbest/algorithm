#include<stdio.h>

/*用函数指针变量作为参数传递给其他函数*/
void main(){
	int a,b;
	int min(int,int);/*函数声明*/
	int max(int,int);/*函数声明*/
	int sum(int,int);/*函数声明*/
	void process(int x,int y,int(*fun)());//函数声明
	a = 5,b = 8;
	printf("a=%d,b=%d\n",a,b);
	printf("max=");
	process(a,b,max);
	printf("min=");
	process(a,b,min);
	printf("sum=");
	process(a,b,sum);
}

/*求最小值函数*/
int min(int x,int y){
	int z;
	if(x>y) z = y;
	else z = x;
	return z;
}

/*求最大值函数*/
int max(int x,int y){
	return (x>y)?x:y;
}

/*求和函数*/
int sum(int x,int y){
	return x+y;
}

void process(int x,int y,int (*fun)()){//这里也可以指定参数(*fun)(int,int)
	int result;
	result = (*fun)(x,y);
	printf("%d\n",result);
}