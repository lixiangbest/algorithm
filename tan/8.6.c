#include<stdio.h>

void main(){
	char str1[5]="love",str2[]=" in China";
	char str3[30];
	char str4[5][6];
	void strcon(char str1[],char str2[],char str3[]);
	int i;
	strcon(str1,str2,str3);
	/*
	for(i=0;i<30;i++){
		printf("%c ",str3[i]);
	}
	*/
	printf("str1:%s\n",str1);
	printf("str2:%s\n",str2);
	printf("connect string:%s",str3);
}

void strcon(char cstr1[],char cstr2[],char cstr3[]){
	int i,j;
	for(i=0;cstr1[i]!='\0';i++){
		cstr3[i] = cstr1[i];
	}
	for(j=0;cstr2[j]!='\0';j++){
		cstr3[i++] = cstr2[j];
	}
	cstr3[i] = '\0';
}