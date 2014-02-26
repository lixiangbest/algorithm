#include<stdio.h>

void main(){
	struct X{int a;char b;int c;}x1;
	struct Y{int a;char b;int c;char d;}y1;
	printf("sizeof X = %d\n", sizeof(struct X));
	printf("sizeof x = %d\n\n", sizeof(x1));
	printf("sizeof Y = %d\n", sizeof(struct Y));
	printf("sizeof Y = %d\n", sizeof y1);
}