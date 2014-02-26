#include<stdio.h>
#include<stdlib.h>
#define N 3
struct student{
	long num;
	char str[15];
	float score[3];
	float avg;
}stu[N+1],newstu[N+1];
#define Len sizeof(struct student)

void main(){
	char *filename = "../13.7.txt";
	char *file = "../13.8.txt";
	FILE *fp;
	struct student sp,*st=&sp,stu_new;
	int i,j,index;
	if((fp=fopen(filename,"r"))==NULL){
		printf("can not open file.");
		exit(0);
	}
	printf("output the ordered student information:\n");
	for(i=0;i<N;i++){
		fread(&stu[i], Len, 1, fp);
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", stu[i].num, stu[i].str, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].avg);
	}
	printf("insert the new student information about num,name,score[3]:\n");
	scanf("%d %s %f %f %f", &stu_new.num, stu_new.str, &stu_new.score[0], &stu_new.score[1], &stu_new.score[2]);
	stu_new.avg = (stu_new.score[0]+stu_new.score[1]+stu_new.score[2])/3;
	//insert order
	for(i=0;i<N;i++){
		if(stu_new.avg<stu[i].avg){
			index = i;
		}
	}
	for(j=index+1;j<N+1;j++){
		*st = stu[j];
		stu[j] = stu_new;
		stu_new = *st;
	}
	printf("output the ordered student information after inserting:\n");
	//write the new orderd value.
	if((fp=fopen(file,"w+"))==NULL){
		printf("can not open file.");
		exit(0);
	}
	for(i=0;i<N+1;i++){
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", stu[i].num, stu[i].str, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].avg);
		printf("Location:%d\n", ftell(fp));
		fwrite(&stu[i], Len, 1, fp);
	}
	rewind(fp);
	printf("\noutput the student information from file:\n");
	for(i=0;i<N+1;i++){
		printf("Location:%d\n", ftell(fp));
		fread(&newstu[i], Len, 1, fp);
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", newstu[i].num, newstu[i].str, newstu[i].score[0], newstu[i].score[1], newstu[i].score[2], newstu[i].avg);
	}
}