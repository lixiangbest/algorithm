#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 3

void main(){
	FILE *fp;
	char *f1="../13.5a.txt",*f2="../13.5b.txt",*f="../13.5.txt";
	char c[100],t,ch;
	int i=0,count,j,tmp;
	if((fp=fopen(f1,"r"))==NULL){
		printf("Can not open the file\n");
		exit(0);
	}
	//read txt file
	printf("file %s\n",f1);
	while((ch=fgetc(fp))!=EOF){
		c[i] = ch;
		putchar(c[i]);
		i++;
	}
	fclose(fp);
	if((fp=fopen(f2,"r"))==NULL){
		printf("Can not open the file\n");
		exit(0);
	}
	printf("\nfile %s\n",f2);
	while((ch=fgetc(fp))!=EOF){
		c[i] = ch;
		putchar(c[i]);
		i++;
	}
	count = i;
	printf("\n%s",c);
	fclose(fp);
	for(i=0;i<count-1;i++){
		for(j=i+1;j<count;j++){
			if(c[i]>c[j]){
				tmp = c[i];
				c[i] = c[j];
				c[j] = tmp;
			}
		}
	}
	c[count] = '\0';
	printf("\norder string:%s",c);
	fp = fopen(f,"w");
	i = 0;
	while(c[i]!='\0'){
		putc(c[i],fp);
		i++;
	}
	fclose(fp);
}