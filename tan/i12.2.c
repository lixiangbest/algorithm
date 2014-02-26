#include<stdio.h>

void main(){
	unsigned m,b,c,d,e=0;
	int i,j;
	printf("Enter the value of m:\n");
	scanf("%o",&m);//101675
	for(i=0;i<=30;i=i+2){//move times.
		b = m>>i;
		c = ~(~0<<1);
		d = b&c;
		e = d<<(i/2)|e;
	}
	printf("e = %o,%d",e,e);
}