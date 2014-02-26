#include<stdio.h>

void main(){
	int i = 2, p, m = 2;
	p = f(i,++i);
	printf("p=%d i=%d\n",p,i);
	p = f(m,m++);
	printf("p=%d m=%d\n",p,m);
	printf("i=%d ++i=%d\n",i,++i);
	printf("m=%d m++=%d\n",m,m++);
}

int f(int a, int b){
	int c;
	printf("a=%d b=%d\n",a,b);
	if(a>b) c = 1;
	else if(a==b) c = 0;
	else c = -1;
	return(c);
}