#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 4
struct newemployee{
	char name[30];
	int salary;
}newemp[N],new_emp[N],new[N];
#define Len sizeof(struct newemployee)

void main(){
	char *filename = "../13.10a.txt";
	char *file = "../13.11.txt";
	char name[10];
	FILE *fp1,*fp2;
	int i;
	if((fp1=fopen(filename,"rb"))==NULL){
		printf("can not open file.");
		exit(0);
	}
	if((fp2=fopen(file,"wb+"))==NULL){
		printf("can not open file.");
		exit(0);
	}
	printf("output the name,num,gender,age,addr,salary,healthy,edu value:\n");
	for(i=0;i<N;i++){
		fread(&newemp[i], Len, 1, fp1);
		printf("%-5s %-4d\n",newemp[i].name,newemp[i].salary);
		strcpy(new_emp[i].name,newemp[i].name);
		new_emp[i].salary = newemp[i].salary;
	}
	printf("Enter the string that you want to delete:\n");
	scanf("%s",name);
	for(i=0;i<N;i++){
		//not equal,write it.
		if(strcmp(name,new_emp[i].name)){
			fwrite(&newemp[i], Len, 1, fp2);
		}
	}
	rewind(fp2);
	printf("output the new employees name,salary information after deleting it:\n");
	for(i=0;i<N;i++){
		fread(&new[i], Len, 1, fp2);
		printf("%-15s %-4d\n",new[i].name,new[i].salary);
	}
	fclose(fp1);
	fclose(fp2);
}