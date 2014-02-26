#include<stdio.h>

int A=1;//define global variable
int B;
void main(){
	int power(int);//declare the caller function
	int b=3,c,d,m=5;
	c=A*b;
	printf("B = %d\n",B);
	printf("%d * %d=%d\n",A,b,c);
	d=power(m);
	printf("%d ** %d=%d",A,m,d);
}