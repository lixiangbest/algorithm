#include<stdio.h>

void main(){
	int i=0;
	int length=0,count=0,location=0;
	char str[50];
	printf("please enter a string\n");
	gets(str);
	while(str[i]!='\0'){
		count = 0;
		while(str[i]!=' '&&str[i]!='\0'){
			count++;
			i++;
		}
		// if current char is blank.
		if(length<count){
			length = count;
			location=i-count;
		}
		i++;//notice it
	}
	for(i=location;str[i]!='\0'&&str[i]!=' ';i++){
		printf("%c",str[i]);
	}
}