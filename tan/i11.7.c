#include<stdio.h>
#define null 0

struct student{
	long num;
	float score;
	struct student *next;
};

void main(){
	struct student a,b,c,*head,*p;
	a.num = 99101; a.score = 89.5;
	b.num = 99103; b.score = 90;
	c.num = 99107; c.score = 85;//assign value to node
	head = &a;//assign the starting address of a to head
	a.next = &b;//assign the starting address of b to the pointer member of a.
	b.next = &c;//assign the starting address of c to the pointer member of b.
	c.next = NULL;//set the pointer member of the end of node to be NULL.
	p = head;//let p point a node.
	do{
		printf("%ld %5.1f\n",p->num,p->score);//output the data of node which is pointed by p.
		p = p->next;//make p point the next node.
	}while(p!=NULL);//complishing output the c node, the value of p is NULL.
	printf("\n");
	do{
		printf("%ld %5.1f\n",head->num,head->score);
		head = head->next;
	}while(head!=null);
}