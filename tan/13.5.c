#include<stdio.h>
#include<stdlib.h>

void main(){
	FILE *fp,*fp1,*fp2;
	FILE *get_fp();
	char *file_read(FILE *);
	char *str,*str1,*str2,*temp;
	int i=0;
	fp1 = get_fp("../13.5a.txt","r");
	str1 = file_read(fp1);
	printf("%s\n",str1);
	fp2 = get_fp("../13.5b.txt","r");
	str2 = file_read(fp2);
	printf("%s\n",str2);
	printf("%s\n",str1);
	fp = get_fp("../13.5.txt","w");
	while(*str1!='\0'){
		*(str+i) = *str1;
		str1++;i++;
	}
	printf("%s\n",str);
	while(*str2!='\0'){
		*(str+i) = *str2;
		str2++;i++;
	}
	*(str+i) = '\0';
	printf("%s\n",str);
	while(*str!='\0'){
		//printf("%c",*str);
		fputc(*str,fp);
		str++;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp);
}

FILE *get_fp(char *filename,char *style){
	FILE *fp;
	if((fp=fopen(filename,style))==NULL){
		printf("Cannot open file.\n");
		exit(0);
	}
	return fp;
}

char *file_read(FILE *fp){
	int i=0;
	char *str,ch;
	//rewind(fp);
	ch = fgetc(fp);
	printf("Location:%d\n",ftell(fp));
	while(ch!=EOF){
		*(str+i) = ch;
		ch = fgetc(fp);
		i++;
	}
	//rewind(fp);
	*(str+i) = '\0';
	return str;
}

