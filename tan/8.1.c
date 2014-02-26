#include<stdio.h>

void main(){
	int num1=15,num2=25;
	int min,max;
	int getmin(int,int);
	int getmax(int,int);
	scanf("%d %d",&num1,&num2);
	printf("num1=%3d num2=%3d\n",num1,num2);
	printf("min=%3d max=%3d",getmin(num1,num2),getmax(num1,num2));
}

int getmax(int a, int b){
	int rest;
	do{
		rest = a%b;
		a=b;
		b=rest;
	}while(rest!=0);
	return a;
}

int getmin(int a, int b){
	int rest;
	rest = a*b/getmax(a,b);
	return rest;
}