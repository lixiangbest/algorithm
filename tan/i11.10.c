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
	struct student *makeit(),*head=NULL;
	struct student *del(struct student *,long);
	long int num;
	head = makeit();
	print(head);
	printf("Please enter a value which needs to be deleted:\n");
	scanf("%ld",&num);
	head = del(head,num);
	printf("Please enter a value which needs to be deleted:\n");
	scanf("%ld",&num);
	head = del(head,num);
	print(head);
}

struct student *del(struct student *head,long num){
	struct student *p1,*p2;
	if(head==NULL){
		printf("\nlist null! \n");
		goto end;
	}
	p1 = head;
	while(num!=p1->num&&p1->next!=NULL){//p1 does not point the searching node,and in the end of nodes.
		p2 = p1;p1 = p1->next;//p1 point the back node.
	}
	if(num==p1->num){//find
		if(p1==head) head = p1->next;//p1 point the head of node,assgin the address of second node to head.
		else p2->next = p1->next;//assign the next node address to the previous node address.
		printf("delete:%ld\n",num);
		n = n-1;
	}else printf("\n%ld not been found! \n",num);
	end: //goto sentence 
	return head;
}

struct student *makeit(){
	struct student *head,*p1,*p2;	
	p1 = (struct student *)malloc(Len);
	head = p1;
	p1->num = 7010;p1->score = 98.5;
	p2 = p1;
	p1 = (struct student *)malloc(Len);
	p1->num = 7008;p1->score = 98.5;
	p2->next = p1;
	p2 = p1;
	p1 = (struct student *)malloc(Len);
	p1->num = 7009;p1->score = 100;
	p2->next = p1;
	p2 = p1;
	p2->next = NULL;
	n = 3;
	return head;
}