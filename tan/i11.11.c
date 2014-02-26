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
	//int t = 0;
	printf("\nNow,These %d records are:\n",n);
	p = head;
	if(head!=NULL){
		do{
			printf("%ld %5.1f\n", p->num, p->score);
			//t++;
			p = p->next;
			//if(t>10) break;
		}while(p!=NULL);
	}
}

void main(){
	struct student *makeit(),*head=NULL,*stud;
	struct student *del(struct student *,long);
	struct student *insert(struct student *head,struct student *stud);
	long int num;
	head = makeit();
	print(head);
	stud->num = 7010;stud->score = 99.5;//stud = (struct student*)malloc(sizeof(struct student));
	head = insert(head,stud);//when you should insert more than one node,you should malloc a new address.
	print(head);
	stud->num = 7013;stud->score = 90.5;//notice the value changed in the chain table.
	head = insert(head,stud);
	//print(head);
}

//insert a value of a ordered chain node table.
struct student *insert(struct student *head,struct student *stud){
	struct student *p0,*p1,*p2;
	p1 = head;//p1 point the first node.
	p0 = stud;//p0 point the node being inserted.
	if(head==NULL){//previous node table is null
		head = p0;
		p0->next = NULL;//the node pointed by p0 is as head point.
	}else{
		while((p0->num > p1->num)&&(p1->next != NULL)){
			p2 = p1;//make p2 point the node just pointed by p1 
			p1 = p1->next;//make p1 point the backward node.
		}
		if(p0->num <= p1->num){
			if(head==p1) head = p0;//insert the value in the head of the chain node.
			else p2->next = p0;//insert the value backward of node pointed by p2.
			p0->next = p1;//notice p0,p1 point the same node.
			//printf("\n%ld\n",p0->num);
			//printf("\n%ld\n",p1->num);
		}else{
			p1->next = p0;
			p0->next = NULL;//insert the value in the end of chain table.
		}
	}
	n++;//the amount of node add 1.
	return head;
}

//create a chain node table.
struct student *makeit(){
	struct student *head,*p1,*p2;	
	p1 = (struct student *)malloc(Len);
	head = p1;
	p1->num = 7008;p1->score = 98.5;
	p2 = p1;
	p1 = (struct student *)malloc(Len);
	p1->num = 7009;p1->score = 98.5;
	p2->next = p1;
	p2 = p1;
	p1 = (struct student *)malloc(Len);
	p1->num = 7012;p1->score = 100;
	p2->next = p1;
	p2 = p1;
	p2->next = NULL;
	n = 3;
	return head;
}