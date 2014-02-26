#include<stdio.h>
#include<stdlib.h>

void main(){
	FILE *fp;
	char ch;
	if((fp=fopen("../13.4.txt","w+"))==NULL){
		printf("Cannot open file.\n");
		exit(0);
	}
	ch = getchar();
	while(ch!='#'){
		ch = ch + 'A'-'a';
		putc(ch,fp);
		ch = getchar();
	}
	fclose(fp);
}
