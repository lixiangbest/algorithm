#include<stdio.h>
#include<stdlib.h>
#define Len sizeof(struct student)
struct student{
	long num;
	float score;
	struct student *next;
};
int n;//n is global variable,can be used in the all functions of the current file.

void print(struct student *head){
	struct student *p;
	printf("\nNow,These %d records are:\n",n);
	p = head;
	if(head!=NULL){
		do{
			printf("%ld %5.1f\n", p->num, p->score);
			p = p->next;
		}while(p!=NULL);
	}
}

void main(){
	struct student *makeit();
	print(makeit());
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