#include<stdio.h>

//内存地址的最小单位是1个byte
void main(){
	//struct关键字的使用之空结构体多大？
	struct student{}stu;//gcc下是0
	//stu是变量，struct student是类型
	printf("Sizeof empty struct var is:%d,%d",sizeof(stu),sizeof(struct student));
}