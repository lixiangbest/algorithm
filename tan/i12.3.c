#include<stdio.h>

void main(){
	//http://longziyongcf.238.idcice.net/displayContent.asp?id=301
	unsigned m,result;
	int n;
	printf("Enter the value of m:\n");
	scanf("%o %o", &m, &n);//113755 113755
	printf("%o\n", m>>1);
	printf("%o\n", n>>1);
	//logic right move
	m >>= 1;
	result = (~0)<<(2*8-1);
	result = (~0)^(result);
	result |= m;
	printf("%o\n", result);
}