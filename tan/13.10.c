#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 4
struct employee{
	char name[30];
	long num;
	char gender;
	int age;
	char addr[30];
	int salary;
	char healthy[20];
	char edu[15];
}emp[N];
struct newemployee{
	char name[30];
	int salary;
}newemp[N],new_emp[N];
#define Len sizeof(struct employee)
#define newLen sizeof(struct newemployee)

void main(){
	char *filename = "../13.10.txt";
	char *file = "../13.10a.txt";
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
		//printf("enter the name,num,gender,age,addr,salary,healthy,edu value %d:\n",i+1);
		//scanf("%s %d %c %d %s %d %s %s", emp[i].name, &emp[i].num, &emp[i].gender, &emp[i].age, emp[i].addr, &emp[i].salary, emp[i].healthy, emp[i].edu);
		//fwrite(&emp[i], Len, 1, fp1);
		fread(&emp[i], Len, 1, fp1);
		printf("%-8s %-3d %-4c %-3d %-8s %-4d %-8s %8s\n",emp[i].name, emp[i].num, emp[i].gender, emp[i].age, emp[i].addr, emp[i].salary, emp[i].healthy, emp[i].edu);
		strcpy(newemp[i].name,emp[i].name);
		newemp[i].salary = emp[i].salary;
		fwrite(&newemp[i], newLen, 1, fp2);
	}
	rewind(fp2);
	printf("output the new employees name,salary information:\n");
	for(i=0;i<N;i++){
		fread(&new_emp[i], newLen, 1, fp2);
		printf("%-15s %-4d\n",new_emp[i].name,new_emp[i].salary);
	}
	fclose(fp1);
	fclose(fp2);
}