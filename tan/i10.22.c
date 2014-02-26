#include<stdio.h>

void main(){
	char *a = "I love China!";
	int i;
	char *forp;
	char fora[] = "\n%s";
	forp = "\n%s";
	printf("%s\n",a);
	printf("The sixth character is:%c\n",a[5]);
	for(i=0;a[i]!='\0';i++){
		printf("%c",a[i]);
	}
	printf(forp,a);
	printf(fora,a);
	
	printf("\n%d %d",a,&a[0]);
}