#include<stdio.h>

#define N 10

/*
char *func(void){
	char destCharArray_a[N] = "lixiang";
	//destCharArray属于局部变量，位于栈内存中
	//在func结束时被释放，所以返回destCharArray将导致错误
	//return语句不可返回指向"栈内存"的"指针"，因为该内存在函数体结束时被自动销毁
	return destCharArray_a;
}
*/

char add(int a,int b){
	return;
}

void main(){
	//char destCharArray_a[N] = "lijun";
	char *pChar;
	//pChar = func();
	//printf("%s",pChar);
	printf("%d",add(2,3));
}