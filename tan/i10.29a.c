#include<stdio.h>

void main(int argc,char *argv[]){
	while(argc>0){
		printf("%s%c",*argv,(argc>0)?' ':'\n');
		++argv;
		--argc;
	}
}