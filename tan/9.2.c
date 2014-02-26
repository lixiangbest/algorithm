#include<stdio.h>
#define Mod(a,b) t=a%b;

void main(){
	int a,b,t;
	printf("enter the a and b value:\n");
	scanf("%d %d",&a,&b);
	Mod(a,b);
	printf("t=%d",t);
}