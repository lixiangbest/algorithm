#include<stdio.h>

//undef撤销宏定义
void main(){
	#define PI 3.141592654
	int m = PI;
	float f = PI;
	printf("int m = %d\n",m);
	printf("float f= %f, f*2 = %f\n",f,f*2);
	printf("float PI = %f, PI*2 = %f\n",PI,PI*2);
	// 撤销宏定义
	#undef PI
	//下面代码不能使用PI了
	//m = PI;//报错：PI未声明
	
	#define X 3
	#define Y X*2
	#undef X
	#define X 2
	int z = Y;
	printf("\nint z = %d",z);
}