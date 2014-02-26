#include<stdio.h>
#define SYS 32-16

void main(){
	unsigned a;
	int start,end;
	unsigned getbits(unsigned,int,int);
	printf("enter the a,start,end:\n");
	scanf("%o %d %d", &a, &start, &end);//101675 5 8
	printf("the change is:%o\n",getbits(a,start,end));
}

unsigned getbits(unsigned m,int s,int e){
	unsigned b,c;
	b = m>>(SYS-e-1);//32 bytes operation system.
	c = ~(~0<<(e-s+1));
	printf("b=%o,c=%o\n",b,c);//octal
	return b&c;
}