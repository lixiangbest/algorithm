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
	FILE *fp;
	int i;
	if((fp=fopen(filename,"w+"))==NULL){
		printf("can not open file.");
		exit(0);
	}
	for(i=0;i<N;i++){
		printf("enter the num,str,score[3] value %d:\n",i+1);
		scanf("%d %s %f %f %f",&stu[i].num, stu[i].str, &stu[i].score[0], &stu[i].score[1], &stu[i].score[2]);
		stu[i].avg = (stu[i].score[0] + stu[i].score[1] + stu[i].score[2])/3;
		fwrite(&stu[i], Len, 1, fp);
	}
	rewind(fp);
	for(i=0;i<N;i++){
		fread(&stu[i], Len, 1, fp);
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", stu[i].num, stu[i].str, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].avg);
	}
	fclose(fp);
}