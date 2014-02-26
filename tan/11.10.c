#include<stdio.h>
#include<stdlib.h>
typedef struct student{
	long int num;
	char *name;
	struct student *next;
}ST;
//#define ST struct student
#define Len sizeof(ST)

void main(){
	ST *create(int);
	void print(ST *);
	ST *com_delete(ST *,ST *);
	ST *head1,*head2,*head;//head1,head2 is not a exact address value.
	head1 = create(1);
	printf("Print chain table 1:\n");
	print(head1);
	
	head2 = create(0);
	printf("\nPrint chain table 2:\n");
	print(head2);
	printf("\nPrint the order and combine table:\n");
	head1 = com_delete(head1,head2);
	print(head1);
}

ST *com_delete(ST *head1,ST *head2){//delete the value in head1 where is also in the head2.
	ST *p,*head = head1;
	ST *p_before;//store the font node of same node.
	ST *p_same=NULL;//store the same node pointer in head.
	//search the value which is in head1 and head2.delete it from head1.
	while(head){//find the min node.
		p = head2;
		while(p){
			if(p->num == head->num){
				p_same = head;//store the font node of the min pointer
				break;
			}
			p = p->next;
		}
		//printf("\n%d\n",p_same->num);
		if(p_same==head1){//if the first node of head1.
			head1 = head1->next;
			p_before = head;
		}else if(p_same!=NULL){
			p_before->next = p_same->next;//delete the common node.
		}else{//if not the same.
			p_before = head;
		}
		p_same = NULL;
		head = head->next;
	}
	return head1;
}

ST *create(int n){
	ST *head,*p1,*p2;
	if(n){
		p1 = (ST *)malloc(Len);//notice the type change.
		head = p2 = p1;
		p1->num = 102;
		p1->name = "Li Lei";
		
		p1 = (ST*)malloc(Len);
		p1->num = 108;
		p1->name = "Han Lei";
		p2->next = p1;
		p2 = p1;
		
		p1 = (ST*)malloc(Len);
		p1->num = 101;
		p1->name = "Han Meimei";
		p2->next = p1;
		p2 = p1;
		
		p2->next = NULL;
	}else{
		p1 = (ST *)malloc(Len);
		head = p2 = p1;
		p1->num = 103;
		p1->name = "Li Ming";
		
		p1 = (ST *)malloc(Len);
		p1->num = 101;
		p1->name = "Li Lei";
		p2->next = p1;
		p2 = p1;
		
		p1 = (ST *)malloc(Len);
		p1->num = 104;
		p1->name = "Li Yuan";
		p2->next = p1;
		p2 = p1;
		
		p1 = (ST *)malloc(Len);
		p1->num = 102;
		p1->name = "Li Yuan";
		p2->next = p1;
		p2 = p1;
		
		p2->next = NULL;
	}
	return head;
}

void print(ST *head){
	ST *p=head;
	if(p==NULL){
		printf("p is null.\n");
		return;
	}
	while(p){
		printf("%ld %s\n",p->num,p->name);
		p = p->next;
	}
}