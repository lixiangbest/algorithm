#include<stdio.h>

void main(){
	FILE *fp1, *fp2;
	fp1 = fopen("../i13.3b.txt","r");
	fp2 = fopen("../i13.4.txt","w");
	while(!feof(fp1)){
		putchar(getc(fp1));
	}
	rewind(fp1);
	while(!feof(fp1)){
		putc(getc(fp1),fp2);
	}
	fclose(fp1);fclose(fp2);
}