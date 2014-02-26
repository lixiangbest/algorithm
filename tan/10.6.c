#include<stdio.h>

void main(){
	char str[80],*p=str;
	int (*fun)();//pointer to function
	int getlen(char*);
	fun = getlen;
	printf("Enter a string:\n");
	scanf("%s",p);
	p = str;
	printf("The length of string:%d",(*fun)(p));
}

int getlen(char *p){
	int len=0;
	while(*p++){
		len++;
	}
	return len;
}

