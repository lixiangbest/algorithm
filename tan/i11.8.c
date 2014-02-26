#include<stdio.h>
#include<stdlib.h>
#define Len sizeof(struct student)
struct student{
	long num;
	float score;
	struct student *next;
};
int n;//n is global variable,can be used in the all functions of the current file.
struct student *creat(){//define function which returns a pointer to the head of chain table.
	struct student *head;
	struct student *p1,*p2;
	n = 0;
	p1 = p2 = (struct student*)malloc(Len);//create a new stored unit.force to change the pointer type.
	printf("Enter the value of num,score until num is 0:\n");
	scanf("%ld %f",&p1->num,&p1->score);
	head = NULL;
	while(p1->num!=0){//if the num is 0,end creating chain table.
		n = n+1;
		if(n==1) head = p1;
		else p2->next = p1;//p1 is at the end of p2
		p2 = p1;//p2 and pointer to the new created value.
		p1 = (struct student*)malloc(Len);//create a new stored unit which pointed by p1;
		scanf("%ld %f",&p1->num,&p1->score);
	}
	p2->next = NULL;//finish creating chain table.
	return head;//return the head address of the chain table.
}

void main(){
	struct student *mhead,*mp;
	struct student *makeit();
	mhead = creat();
	printf("Output the value of chain table:\n");
	while(mhead){
		printf("Num:%ld, score:%f\n",mhead->num,mhead->score);
		mhead = mhead->next;
	}
	printf("\n");
	mp = makeit();
	printf("Output the value of chain table:\n");
	while(mp){
		printf("Num:%ld, score:%f\n",mp->num,mp->score);
		mp = mp->next;
	}
}

struct student *makeit(){
	struct student *head,*p1,*p2;
	n = 0;
	printf("Enter the value of num,score until num is 0:\n");
	while(1){
		p1 = (struct student *)malloc(Len);
		scanf("%ld %f", &p1->num, &p1->score);
		if(p1->num==0) break;
		n++;
		if(n==1){head = p1;}
		else p2->next = p1;
		p2 = p1;
	}
	p2->next = NULL;
	return head;
}
