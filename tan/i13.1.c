#include<stdio.h>
#include<stdlib.h>

void main(){
	FILE *fp;
	char ch,filename[20] = "../i13.1.txt";
	printf("Please enter the name of the file name:\n");
	if((fp=fopen(filename,"a"))==NULL){
		printf("Can not open file.\n");
		exit(0);
	}
	puts(filename);
	printf("%s",filename);
	scanf("%s",filename);
	//printf("%s",filename);
	//ch = getchar();//receive the last enter char(\n) when calling the function of scanf.
	//printf("%c",ch);
	ch = getchar();//receive the first char
	while(ch!='#'){
		fputc(ch,fp);putchar(ch);
		ch = getchar();
	}
	fclose(fp);
}