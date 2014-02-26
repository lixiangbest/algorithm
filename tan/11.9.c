#include<stdio.h>
#include<stdlib.h>
typedef struct vote{
	long num;
	struct vote *next;
}ST;
#define Len sizeof(ST)
#define N 8

void main(){
	ST *head;
	ST *create();
	void leave(ST *);
	void print(ST *);
	head = create();
	printf("The chain table:\n");
	print(head);
	printf("\nThe left chain table:\n");
	leave(head);
	print(head);
}

void leave(ST *head){
	int i=0,start=1;//i stats the amount of num greater than 0. 
	ST *p = head;
	void print(ST *);
	while(1){//verify the node value is greater than 0
		while(p){
			if(start==3 && p->num > 0){//notice when start=3,you must check the num.
				start = 1;
				p->num = 0;
			}
			if(p->num > 0){
				i++;
				start++;
			}
			p = p->next;
		}
		if(i<=2) break;
		else if(p==NULL){
			p = head;
			i=0;
		}
	}
}

ST *create(){
	ST *head,*p1,*p2;
	int i;
	for(i=1;i<=N;i++){
		p1 = malloc(Len);
		p1->num = i;
		if(i==1) head = p1;
		else p2->next = p1;
		p2 = p1;
	}
	p2->next = NULL;
	return head;
}

void print(ST *head){
	ST *p=head;
	int i=0;
	while(p){
		i++;
		if(p->num>0)	printf("index:%d %-4d\n",i,p->num);
		p = p->next;
	}
}