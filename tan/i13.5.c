#include<stdio.h>
#include<stdlib.h>

#define N 4
struct student_type{
	char name[10];
	int num;
	int age;
	char sex;
}stud[N],stuo[N];
#define Len sizeof(struct student_type)

void main(){
	int i,location;
	FILE *fp;
	if((fp=fopen("../i13.5.txt","r+"))==NULL){//w+
		printf("can not open file\n");
		exit(0);
	}
	/*
	printf("Enter the name,num,age,sex:\n");
	for(i=0;i<N;i++){
		scanf("%s %d %d %c", stud[i].name, &stud[i].num, &stud[i].age, &stud[i].sex);
		fwrite(&stud[i], Len, 1, fp);
	}
	rewind(fp);
	*/
	printf("output the name,num,age,sex:\n");
	for(i=0;i<N;i+=2){
		location = ftell(fp);
		printf("Location:%d\n",location);
		fseek(fp,i*Len,0);
		fread(&stuo[i],Len,1,fp);
		printf("%s %d %d %c\n", stuo[i].name, stuo[i].num, stuo[i].age, stuo[i].sex);
	}
	location = ftell(fp);
	printf("Location:%d\n",location);
	fclose(fp);
}