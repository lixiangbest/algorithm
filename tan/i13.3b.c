#include<stdio.h>
#include<stdlib.h>
#define N 5

void main(){
	FILE *fp;
	int i;
	char *s,fcontent[N];
	char *fstr = "../i13.3b.txt";
	if((fp=fopen(fstr,"r"))==NULL){
		printf("Open file error.\n");
		exit(0);
	}
	i = 100;
	s = (char *)&i;
	//putc(s[0],fp);putc(s[1],fp);
	putw(i,fp);
	//i = getw(fp);
	printf("i = %d\n",i);
	s[0] = getc(fp);//I 73
	s[1] = getc(fp);//space 32
	printf("i = %d %d\n", s[0], s[1]);
	fclose(fp);
	fp = fopen(fstr,"r+");//w+
	fputs("I like!\nI love In China!",fp);
	rewind(fp);
	fgets(fcontent, N, fp);
	printf("File contents:%s",fcontent);
}