#include<stdio.h>
#include<stdlib.h>
typedef struct student{
	long int num;
	int year;
	char *name;
	struct student *next;
}ST;
//#define ST struct student
#define Len sizeof(ST)

void main(){
	ST *create();
	void print(ST *);
	ST *delete(ST *,int);
	ST *head;//head is not a exact address value.
	int year;
	head = create();
	printf("Print chain table:\n");
	print(head);
	
	printf("\nEnter the year of node being deleted:\n");
	scanf("%d",&year);
	printf("\nPrint the deleted chain table:\n");
	head = delete(head,year);
	print(head);
}

ST *delete(ST *head,int year){
	ST *p1=head,*p2;
	while(year!=p1->year&&p1->next!=NULL){
		p2 = p1;//store the previous node of p1.
		p1 = p1->next;//assign the next node to p1.
	}
	//if find it, delete it.
	if(year==p1->year){
		if(p1==head) head = p1->next;
		else p2->next = p1->next;
	}else{
		printf("\nNot found!\n");
	}
	return head;
}

ST *create(){
	ST *head,*p1,*p2;
	p1 = (ST *)malloc(Len);//notice the type change.
	head = p2 = p1;
	p1->num = 102;
	p1->year = 18;
	p1->name = "Li Lei";
	
	p1 = (ST*)malloc(Len);
	p1->num = 108;
	p1->year = 25;
	p1->name = "Han Lei";
	p2->next = p1;
	p2 = p1;
	
	p1 = (ST*)malloc(Len);
	p1->num = 101;
	p1->year = 29;
	p1->name = "Han Meimei";
	p2->next = p1;
	p2 = p1;
	
	p2->next = NULL;
	return head;
}

void print(ST *head){
	ST *p=head;
	if(p==NULL){
		printf("p is null.\n");
		return;
	}
	while(p){
		printf("%ld %s %d\n",p->num,p->name,p->year);
		p = p->next;
	}
}