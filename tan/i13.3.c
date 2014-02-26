#include<stdio.h>
#define Size 4
struct student_type{
	char name[10];
	int num;
	int age;
	char addr[15];
}stud[Size];
#define Len sizeof(struct student_type)
char *filename = "../i13.3.txt";

void save(){
	FILE *fp;
	int i;
	if((fp=fopen(filename,"wb"))==NULL){//== is superior to =
		printf("cannot open file\n");
		return;
	}
	for(i=0;i<Size;i++){
		if(fwrite(&stud[i],Len,1,fp)!=1)
			printf("file write error\n");
	}
	fclose(fp);
}

void main(){
	int i,count;
	FILE *fp;
	/*
	for(i=0;i<Size;i++){
		printf("print the student name,num,age,addr of %d:\n",i+1);
		scanf("%s %d %d %s", stud[i].name, &stud[i].num, &stud[i].age, &stud[i].addr);
	}
	save();
	*/
	fp = fopen(filename,"rb");//lijun lixiang lilin lineng
	printf("Struct char = %d, int = %d, len = %d\n",sizeof(char),sizeof(int),Len);
	//get two students info to stud[0],stud[1];stud[1] is covered when i is 1.
	for(i=0;i<Size;i++){
		count = fread(&stud[i],Len,2,fp);//1 change to 3.
		printf("count = %d\n",count);
		printf("%-10s %4d %4d %-15s\n", stud[i].name, stud[i].num, stud[i].age, stud[i].addr);
	}
	printf("\n");
	for(i=0;i<Size;i++){
		count = fread(&stud[i],Len,1,fp);//1 change to 3
		printf("count = %d\n",count);
		printf("%-10s %4d %4d %-15s\n", stud[i].name, stud[i].num, stud[i].age, stud[i].addr);
	}
	fclose(fp);
}