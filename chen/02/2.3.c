#include<stdio.h>

void main(){
	int n = 1;
	char c = '1';
	char s[] = "1";
	printf("sizeof 1:%d\n",sizeof(n));
	printf("sizeof '1':%d\n",sizeof(c));
	printf("sizeof \"1\":%d\n",sizeof(s));
}