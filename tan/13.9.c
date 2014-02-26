#include<stdio.h>
#include<stdlib.h>
#define N 4
#define M 3
struct student{
	long num;
	char str[15];
	float score[M];
	float avg;
}stu[N],newstu[N];
#define Len sizeof(struct student)

void main(){
	char *filename = "../13.8.txt";
	char *file = "../13.9.txt";
	FILE *fp;
	struct student sp,stu_new;
	int i,j,k;
	float tmp;
	if((fp=fopen(filename,"r"))==NULL){
		printf("can not open file.");
		exit(0);
	}
	printf("output the ordered student information:\n");
	for(i=0;i<N;i++){
		fread(&stu[i], Len, 1, fp);
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", stu[i].num, stu[i].str, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].avg);
	}
	//insert order
	for(i=0;i<N;i++){
		//bubble order
		for(j=0;j<M-1;j++){//change times
			for(k=j+1;k<M;k++){
				if(stu[i].score[j]<stu[i].score[k]){
					tmp = stu[i].score[j];
					stu[i].score[j] = stu[i].score[k];
					stu[i].score[k] = tmp;
				}
			}
		}
	}
	fclose(fp);
	printf("output the ordered score student information:\n");
	//write the new orderd value.
	if((fp=fopen(file,"w+"))==NULL){
		printf("can not open file.");
		exit(0);
	}
	for(i=0;i<N;i++){
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", stu[i].num, stu[i].str, stu[i].score[0], stu[i].score[1], stu[i].score[2], stu[i].avg);
		printf("Location:%d\n", ftell(fp));
		fwrite(&stu[i], Len, 1, fp);
	}
	rewind(fp);
	printf("\noutput the student information from file:\n");
	for(i=0;i<N;i++){
		printf("Location:%d\n", ftell(fp));
		fread(&newstu[i], Len, 1, fp);
		printf("%-4d %-15s %4.2f %4.2f %4.2f %4.2f\n", newstu[i].num, newstu[i].str, newstu[i].score[0], newstu[i].score[1], newstu[i].score[2], newstu[i].avg);
	}
}