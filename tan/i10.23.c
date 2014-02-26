#include<stdio.h>

void main(){
	int max(int,int);
	int min(int,int);
	int a,b,c;
	int (*p)();
	scanf("%d %d",&a,&b);
	c = max(a,b);
	p = min;//function pointer
	printf("a=%d,b=%d,max=%d\n",a,b,c);
	printf("a=%d,b=%d,min=%d\n",a,b,(*p)(a,b));
}

max(int x,int y){
	int z;
	if(x>y) z = x;
	else z = y;
	return z;
}

min(int x,int y){
	int z;
	if(x<y) z = x;
	else z = y;
	return z;
}