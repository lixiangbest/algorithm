#include<stdio.h>

void main(){
	unsigned a,b,c,d;
	int n;
	printf("enter a,n:\n");
	scanf("%o %d",&a,&n);
	//right loop shift
	b = a<<(32-n);//store the n
	c = a>>n;//store the 16-n
	d = c|b;
	c = c|b;
	printf("a=%o,%d\nb=%o,%d\nc=%o,%d\n",a,a,b,b,c,c);
	printf("d=%o,%d\n",d,d);
}