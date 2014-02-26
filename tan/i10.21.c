#include<stdio.h>

void main(){
	char *a = "I love China!";
	char str[] = "I'm Chinese!";
	printf("%s\n",a);
	a = a+7;
	printf("%s\n",a);
	//str = str+7;//error:when assgining value,the type of variable is not allowed.
	//printf("%s\n",str);
}