#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	FILE *in,*out;
	char ch;
	if(argc!=3){
		printf("You forgot to enter a filename\n");
		exit(0);
	}
	if((in=fopen(argv[1],"r"))==NULL){
		printf("cannot open infile:\n");
		exit(0);
	}
	if((out=fopen(argv[2],"w"))==NULL){
		printf("cannot open outfile:\n");
		exit(0);
	}
	while(!feof(in)){
		fputc(fgetc(in),out);
	}
	fclose(in);
	fclose(out);
}