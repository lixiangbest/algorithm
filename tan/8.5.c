#include<stdio.h>
#include<string.h>

void main(){
	char str[12],temp;
	int len,i;
	printf("Enter a string:\n");
	gets(str);
	len = strlen(str);
	printf("the str length is:%d\n",len);
	for(i=0;i<len/2;i++){
		temp = str[i];
		str[i] = str[len-1-i];
		str[len-1-i] = temp;
	}
	printf("%s",str);
}