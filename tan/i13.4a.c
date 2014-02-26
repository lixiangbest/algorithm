#include<stdio.h>
#include<stdlib.h>

void main(){
	FILE *fp;
	int i;
	float t;
	char str[30],*a=str;
	if((fp=fopen("../i13.4a.txt","w+"))==NULL){
		printf("cannot open file.");
		exit(1);
	}
	printf("write into the file:\n");
	printf("Location:%d %d\n", fp, ftell(fp));
	i = 12;t=13.5;a = "lixiang";
	fprintf(fp,"%d,%6.2f %s\n",i,t,a);
	printf("Location:%d %d\n", fp, ftell(fp));
	i = 15;t=15.5;a = "lineng";
	fprintf(fp,"%d,%6.2f %s",i,t,a);
	printf("Location:%d %d\n", fp, ftell(fp));
	rewind(fp);
	
	printf("\nread frome the file:\n");
	printf("Location:%d %d\n", fp, ftell(fp));
	while(fscanf(fp,"%d,%f %s",&i,&t,a)!=EOF){
		printf("%d,%6.2f %s\n", i, t, a);
		printf("Location:%d %d\n", fp, ftell(fp));
	}
	printf("Location:%d %d\n", fp, ftell(fp));
	fclose(fp);
}