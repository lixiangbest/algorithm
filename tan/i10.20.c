#include<stdio.h>

void copy_string(char from[],char to[]){
	int i=0;
	/*
	while(from[i]!='\0'){
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
	//another method
	*/
	/*
	while(*from!='\0'){
		*to++ = *from++;
	}
	*to = '\0';
	*/
	/*
	while((*to=*from)!='\0'){
		to++;
		from++;
	}
	*/
	/*
	while((*to++=*from++)!='\0');
	//printf("%d",*to);//not a confirmed value.
	*/
	while(*from)
		*to++ = *from++;
	*to = '\0';
}

void main(){
	char a[] = "I am a teacher.";
	char b[] = "you are a student.";
	printf("string a=%s\nstring b= %s\n",a,b);
	copy_string(a,b);
	printf("\nstring a=%s\nstring b= %s\n",a,b);
}