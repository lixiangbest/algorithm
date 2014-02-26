#include<stdio.h>
#define N 3

typedef struct{
	int num;
	float score;
}*link,stu[N];

void out(link p){
	int i=0;
	for(;i<N;i++){
		printf("num=%d score=%f\n",p->num,p->score);
		p++;
	}
}

void change(stu p){
	int i=0;
	for(;i<N;i++){
		p[i].score++;
		//p++;
	}
}

void change1(link p){
	int i=0;
	for(;i<N;i++){
		p[i].score++;
	}
}

void main(){
	stu stu1;
	stu1[0].num = 12;
	stu1[0].score = 78.5;
	stu1[1].num = 13;
	stu1[1].score = 90;
	stu1[2].num = 10;
	stu1[2].score = 95.5;
	printf("before change:\n");
	out(stu1);
	change(stu1);
	printf("\nafter changed:\n");
	out(stu1);
	
	change1(stu1);
	printf("\nafter changed1:\n");
	out(stu1);
}