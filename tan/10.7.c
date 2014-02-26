#include<stdio.h>
#define M 5

void handle(char *p1,char *p2){
	int i=0;
	while(*p1){
		if(i<M-1){
			i++;
		}else{
			*p2 = *p1;
			p2++;
		}
		p1++;
	}
	if(M-1>i){
		printf("The string is too long.");
	}else{
		*p1 = '\0';
	}
}

void main(){
	char *str1;
	char *str2;
	printf("Please enter the str1:\n");
	scanf("%s",str1);
	handle(str1,str2);
	printf("%s",str2);
}