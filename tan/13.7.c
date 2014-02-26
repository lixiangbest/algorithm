#include<stdio.h>
#include<stdlib.h>
#define N 3
struct student{
	long num;
	char str[15];
	float score[3];
	float avg;
}stu[N];

#define Len sizeof(struct student)

void main(){
	char *filename = "../13.6.txt";
	char *file = "../13.7.txt";
	FILE *fp;
	struct student st;
	int i;
	int j;
	if((fp=fopen(filename,"r"))==NULL){
		printf("can not open file.");
		exit(0);
	}
	printf("output the student information:\n");
	for(i=0;i<N;i++){
		fread(&stu[i], Len, 1, fp);
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", stu[i].num, stu[i].str, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].avg);
	}
	printf("output the ordered student information:\n");
	for(i=0;i<N-1;i++){
		for(j=i+1;j<N;j++){
			if(stu[i].avg<stu[j].avg){
				st = stu[i];
				stu[i] = stu[j];
				stu[j] = st;
			}
		}
	}
	fclose(fp);
	if((fp=fopen(file,"w+"))==NULL){
		printf("can not open file.");
		exit(0);
	}
	for(i=0;i<N;i++){
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", stu[i].num, stu[i].str, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].avg);
		fwrite(&stu[i], Len, 1, fp);
	}
	fclose(fp);
	printf("\noutput the student information from file:\n");
	for(i=0;i<N;i++){
		fread(&stu[i], Len, 1, fp);
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", stu[i].num, stu[i].str, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].avg);
	}
}