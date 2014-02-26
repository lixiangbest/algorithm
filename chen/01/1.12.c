#include<stdio.h>

void main(){
	//const修饰只读变量
	const int Max = 5;
	int const i = Max;
	int j=5;
	printf("%d %d",Max,i);
	/*
	//报错：可变大小的对象不能被初始化
	int Array[Max] = {1,3,5,7,10};
	int i;
	for(i=0;i<Max;i++){
		printf("%d ",Array[i]);
	}
	
	//报错：case标号不能还原为一个整常量
	switch(j){
		case Max:
			printf("%d ",Max);
			break;
		default:
			printf("%d ",j);
			break;
	}
	*/
}