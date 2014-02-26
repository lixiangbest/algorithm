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
	int i,j,index=0;
	float sum,max=0,val;
	for(i=0;i<N;i++){
		sum = 0;
		printf("\nthe %d student\n",i);
		printf("%ld %s ", p->num, p->name);
		for(j=0;j<3;j++){
			val = p->score[j];
			printf("%f ",val);
			sum+=val;
			if(val>max){max = val;index = i;}
		}
		printf("\naver:%f\n",sum/3);
		p++;
	}
	p = p-N+index;
	sum = (p->score[0]+p->score[1]+p->score[2])/N;
	printf("\nThe highest score of student:\n");
	printf("%ld %s %f %f %f\naver:%f", p->num, p->name, p->score[0], p->score[1], p->score[2], sum);
}