#include<stdio.h>

void main(){
	char str1[50];
	void longword(char str[]);
	printf("please enter a string:\n");
	gets(str1);
	longword(str1);
}

void longword(char str[]){
	int i=0;
	int length=0,count,location=0;
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