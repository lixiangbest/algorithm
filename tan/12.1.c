#include<stdio.h>

void main(){
	unsigned a,b,c,d;
	scanf("%o",&a);
	b = a>>4;
	c = ~(~0<<4);
	d = b&c;
	printf("a = %o,%d\nb=%o,%d\nc = %o,%d\nd = %o,%d\n",a,a,b,b,c,c,d,d);
}