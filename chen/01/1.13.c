#include<stdio.h>

//const修饰函数的参数
int func(const int i){//告诉编译器i在函数体中不能改变
	//i = 5;//报错：向只读位置'i'赋值
	return i;
}

//const修饰返回值
const int func1(){
	return 15;
}

void main(){
	int const a[5] = {1,2,3,4,5};
	const int b[5] = {6,7,8,9,10};
	int i;
	//const int *p;//p可变，p指向的对象不可变
	//int const *p;//p可变，p指向的对象不可变
	//int *const p;//p不可变，p指向的对象可变
	//const int *const p;//p和p指向的对象都不可变
	int *const p = &i;
	int m;
	printf("int const a:\n");
	for(i=0;i<5;i++){
		printf("%d ",a[i]);
	}
	printf("\nint const b:\n");
	for(i=0;i<5;i++){
		printf("%d ",b[i]);
	}
	//a[4] = 20;//报错：向只读位置'a[4]'赋值
	printf("\n*p = %d",*p);
	printf("\ni = %d",func(i));
	
	m = func1();
	printf("\nm = %d",m);
	m = 17;
	printf("\nm = %d",m);
}