#include<stdio.h>

void main(){
	char spechar[]={'a','e','i','o','u','\0'};
	char input[30];
	char store[30];
	int i,j=0;
	int checkspe(char chchar,char spechar[]);//check if it is a special char.
	gets(input);
	for(i=0;input[i]!='\0';i++){
		if(checkspe(input[i],spechar))	store[j++] = input[i];
	}
	printf("%s",store);
}

int checkspe(char chchar,char schar[]){
	int i;
	for(i=0;schar[i]!='\0';i++){
		if(chchar==schar[i]) return 1;
	}
	return 0;
}