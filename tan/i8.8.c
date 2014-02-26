#include<stdio.h>

void main(){
	int m;
	long int sum;
	long int fac(int);
	printf("input an integer number:");
	scanf("%d",&m);
	sum = fac(m);
	printf("%d! = %4ld", m, sum);
}

long int fac(int x){
	int c;
	if(x==1) c = 1;
	else c = fac(x-1)*x;
	return c;
}