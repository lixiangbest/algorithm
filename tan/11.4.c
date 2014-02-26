#include<stdio.h>
typedef struct{
	long num;
	char name[20];
	float score[3];
}ST;
#define N 3

void main(){
	ST stu[N],*p = stu;
	int i;
	void print(ST *);
	void input(ST *);
	printf("Enter the students num,name,score 0/1/2 records:\n");
	input(p);
	printf("Output the students record:\n");
	print(stu);
}

void input(ST *p){
	int i;
	for(i=0;i<N;i++){
		printf("the %d student\n",i);
		scanf("%ld %s %f %f %f",&p[i].num,p[i].name,&p[i].score[0],&p[i].score[1],&p[i].score[2]);
	}
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