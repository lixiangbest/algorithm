#include<stdio.h>

void main(){
	char str1[80],str2[80];
	int i,max = 80;
	printf("Enter string 1:");
	gets(str1);
	printf("Enter string 2:");
	gets(str2);
	for(i=0;i<max;i++){
		if(str1[i]=='\0'&&str2[i]=='\0'){
			printf("str1 - str2 = %d",0);
			break;
		}else if(str1[i]==str2[i]) continue;
		else{
			printf("str1 - str2 = %d",str1[i]-str2[i]);
			break;
		}
	}
}