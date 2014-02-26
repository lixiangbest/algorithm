#include<stdio.h>

//不加返回值说明的函数为int函数
add(int a,int b){
	return a+b;
}

//fun()函数不接受任何参数
fun(){//前加void报错：无返回值的函数中，return带返回值
	return 1;
}

//fun1(void)函数不接受任何参数
fun1(void){//调用时fun1(2)提示给函数的实参太多
	return 2;
}

void main(){
	printf("2+3=%d\n",add(2,3));
	printf("%d %d\n",fun(2),fun1());
}