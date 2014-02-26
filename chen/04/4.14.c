#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//用return
char* getMemory1(char*p,int num){
	p = (char*)malloc(num*sizeof(char));
	return p;
}

//用二级指针
void getMemory2(char **p,int num){
	*p = (char*)malloc(num*sizeof(char));
	return p;
}

//获取拷贝后的内存
void main(){
	char* str1 = NULL;
	char* str2 = NULL;
	str1 = getMemory1(str1,10);//传值，str1存储的是内存地址值
	strcpy(str1,"Hello");
	printf("%s\n",str1);
	free(str1);
	printf("%p,%p\n",str1,*str1);
	
	//用二级指针
	getMemory2(&str2,10);//传递的是str的地址，是一个值。
	strcpy(str2,"Hello");
	printf("\n%s\n",str2);
	free(str2);
	printf("%p,%p",str2,*str2);
}