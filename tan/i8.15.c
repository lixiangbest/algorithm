#include<stdio.h>

int p=1,q=5;
float f(int a){
	int b;
	b = a+p+q;
	return b;
}

char c1='a',c2='A';
int c(char ch){
	int ich;
	ich = c1+c2;
	return ich;
}


void main(){
	int m,n,d=5;
	float p;
	m = f(2);
	n = c('A');
	p = d;
	//d is integer, when it is forced to output as float, it will get a exact number.
	printf("%d %d %f %f",m,n,p,d);
}