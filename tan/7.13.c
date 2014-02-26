#include<stdio.h>

void main(){
	char s1[] = {"I like China!"};
	char s2[] = {"Someone's watching over me!"};
	char s3[100];
	int i,j,k;
	for(i=0;s1[i]!='\0';i++){
		s3[i] = s1[i];
	}
	for(j=0;s2[j]!='\0';j++){
		s3[i] = s2[j];
		i++;
	}
	s3[i] = '\0';
	for(i=0;s3[i]!='\0';i++){
		printf("%c",s3[i]);
	}
	printf("\n%s",s3);
}