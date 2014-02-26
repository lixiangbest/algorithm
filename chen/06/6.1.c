#include<stdio.h>
#include<stdlib.h>

void main(){
	int c;
	c = getchar();
	printf("%c,%p\n",c,c);
	if(EOF==c){
		printf("End of file\n");
	}else{
		printf("Not end of file\n");
	}
	printf("%p,%d",EOF,EOF);
}