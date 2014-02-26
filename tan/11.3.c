#include<stdio.h>
typedef struct{
	long num;
	char name[20];
	float score[3];
}ST;
#define N 3

void main(){
	ST stu[N];
	int i;
	void print(ST *);
	printf("Enter the students num,name,score 0/1/2 records:\n");
	for(i=0;i<N;i++){
		printf("the %d student\n",i);
		scanf("%ld %s %f %f %f",&stu[i].num,stu[i].name,&stu[i].score[0],&stu[i].score[1],&stu[i].score[2]);
	}
	printf("Output the students record:\n");
	print(stu);
}

void print(ST *p){
	int i,j;
	for(i=0;i<N;i++){
		printf("\nthe %d student\n",i);
		printf("%ld %s ", p->num, p->name);
		for(j=0;j<3;j++){
			printf("%f ",p->score[j]);
		}
		p++;
	}
}