#include<stdio.h>

void main(){
	char string[] = "I love China!";
	printf("%s\n",string);
	printf("%c\n",*(string+3));
}