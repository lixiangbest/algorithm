/**
	通过函数改变指向指针的值
	日期：2012年7月30日
*/
#include<stdio.h>
#include<stdlib.h>

int m = 2, n = 3;
void change(int *p){
	int m;
	//*p = 4;//改变指针指向的值
	p = &n;//改变指针的指向，对实参无影响
}

//改变指针指向的指针，即使指针指向另外的元素
void changeP(int **p){
	int m;
	*p = &n;//改变指针指向的指针
}

void main(){
	int *pm = &m;
	printf("Before change:%d\n",*pm);
	change(pm);
	printf("After change:%d\n",*pm);
	changeP(&pm);
	printf("After changeP:%d\n",*pm);
}