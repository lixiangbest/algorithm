#include<stdio.h>

void main(){
	extern enter_string(char str[80]);
	extern delete_string(char str[],char ch);
	extern print_string(char str[]);
	char c;
	char str[80];
	printf("do %d\n",enter_string(str));
	scanf("%c",&c);
	delete_string(str,c);
	print_string(str);
}