#include<stdio.h>
#include<stdlib.h>

void main(){
	FILE *in,*out;
	char ch,infile[20]="../i13.1.txt",outfile[20]="../i13.2.txt";
	printf("Enter the infile name:%s\n",infile);
	printf("Enter the outfile name:%s\n",outfile);
	if((in=fopen(infile,"r"))==NULL){
		printf("cannot open infile:\n");
		exit(0);
	}
	if((out=fopen(outfile,"w"))==NULL){
		printf("cannot open outfile:\n");
		exit(0);
	}
	while(!feof(in)){
		fputc(fgetc(in),out);
	}
	fclose(in);
	fclose(out);
}