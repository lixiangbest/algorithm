#include<stdio.h>
#include<stdlib.h>
typedef struct student{
	long int num;
	int year;
	char *name;
	struct student *next;
}ST,*List;
//#define ST struct student
#define Len sizeof(ST)

void main(){
	ST *create();
	void print(ST *);
	ST *reverse(ST *);
	ST *head;//head is not a exact address value.
	head = create();
	printf("Print chain table:\n");
	print(head);
	
	printf("\nPrint the deleted chain table:\n");
	head = reverse(head);
	print(head);
}

//reverse the chain table.
ST *reverse(List head){
	ST *t,*p,*q;
	//if the chain table is empty or has only element,return it.
	if(head==NULL||head->next==NULL){
		return head;
	}
	t = NULL;//keep the break node.
	p = head;
	q = head->next;
	while(q!=NULL){
		t = q->next;//keep the break node.
		q->next = p;//reverse the pointer.
		p = q;
		q = t;
	}
	//now q pointer the last element,also head of the reversed chain table.
	head->next = NULL;//set the tail of chain table.
	head = p;//set the header of chain table.
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