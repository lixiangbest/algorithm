#include<stdio.h>
#include<stdlib.h>
char *filename = "../i13.3a.txt";

void main(){
	FILE *fp;
	int i = 3;
	char ch;
	float t = 4.5;
	if((fp=fopen(filename,"w+"))==NULL){
		printf("cannot open file.\n");
		exit(0);
	}
	printf("Because \rof you\n!");
	fprintf(fp,"%d,%6.2f",i,t);
	fscanf(fp,"%d,%f", &i, &t);
	fclose(fp);
	fp = fopen(filename,"r");
	while(!feof(fp)){
		//ch = fgetc(fp));
		putchar(fgetc(fp));
	}
	printf("%d %f",i,t);
}