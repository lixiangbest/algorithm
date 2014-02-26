#include<stdio.h>
#define Change(a,b) t=a;a=b;b=t;

void main(){
	int a,b,t;
	printf("enter the a and b value:\n");
	scanf("%d %d",&a,&b);
	Change(a,b);
	printf("a=%d b=%d\n",a,b);
	printf("a=%d" "b=%d",a,b);
}