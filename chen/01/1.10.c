#include<stdio.h>
#include<memory.h>

#define N 10
void main(){
	//void a;//变量或字段'a'声明为void,void类比为抽象数据类型，正如抽象基类
	//memset和memcpy的使用
	int intArray_a[N];
	char destCharArray_a[N] = "lijun";
	char srcCharArray_a[N] = "nixiang";
	int i;
	printf("Before empty:\n");
	for(i=0;i<N;i++){
		intArray_a[i] = i+1;
		printf("%d ",intArray_a[i]);
	}
	memset(intArray_a,0,(N-1)*sizeof(int));//将intArray_a清0
	printf("\nAfter empty:\n");
	for(i=0;i<N;i++){
		printf("%d ",intArray_a[i]);
	}
	//memcpy使用,将srcCharArray_a拷贝给destCharArray_a
	printf("\nBefore Copy:destCharArray_a:'%s',srcCharArray_a:'%s'",destCharArray_a,srcCharArray_a);
	memcpy(destCharArray_a,srcCharArray_a,(N-7)*sizeof(char));
	printf("\nAfter Copy:destCharArray_a:'%s',srcCharArray_a:'%s'",destCharArray_a,srcCharArray_a);
}