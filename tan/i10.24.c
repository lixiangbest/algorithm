#include<stdio.h>

void main(){
	int max(int,int);
	int min(int,int);
	int add(int,int);
	int process(int,int,int(*fun)());
	int a,b;
	printf("enter a and b:\n");
	scanf("%d %d",&a,&b);
	printf("max=");
	process(a,b,max);
	printf("min=");
	process(a,b,min);
	printf("sum=");
	process(a,b,add);
}

int max(int x,int y){
	int z;
	if(x>y) z = x;
	else z = y;
	return z;
}

int min(int x,int y){
	int z;
	if(x<y) z = x;
	else z = y;
	return z;
}

int add(int x,int y){
	int z;
	z = x+y;
	return z;
}

int process(int x,int y,int (*fun)(int,int)){
	int result;
	result = (*fun)(x,y);
	printf("%d\n",result);
}