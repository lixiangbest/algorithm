#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 3

void main(){
	FILE *fp;
	char str[100];
	int i=0;
	if((fp=fopen("../13.4a.txt","w+"))==NULL){
		printf("Can not open the file\n");
		exit(0);
	}
	printf("Input the string, end with !:\n");
	gets(str);
	while(str[i]!='!'){
		if(str[i]>='a'&&str[i]<='z'){
			str[i] = str[i]+'A'-'a';
		}
		fputc(str[i],fp);
		i++;
	}
	rewind(fp);
	fgets(str,strlen(str)+1,fp);//+1,for '\0'
	printf("%s\n",str);
	fclose(fp);
}