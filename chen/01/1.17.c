#include<stdio.h>
#include<stdlib.h>

// 柔性数组
void main(){
	int i;
	int a[0];
	typedef struct st_type{
		int i;
		//在使用柔性数组时需要把它当做结构体的一个成员。
		//柔性数组其实和结构体没什么关系，算不得结构体的正式成员。
		//C99 a[0]也可
		int a[];//结构体不包含柔性数组的内存大小，柔性数组只是编外人员，不占结构体的编制
	}type_a;
	printf("sizeof int %d,\nsizeof flexible array:%d\n",sizeof i,sizeof(type_a));
	type_a *p = (type_a *)malloc(sizeof(type_a)+100*sizeof(int));
	printf("sizeof struct var after malloc:%d\n",sizeof(*p));
}