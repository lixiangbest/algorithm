#include<stdio.h>
#include<stdlib.h>
typedef struct student{
	long int num;
	float score;
	struct student *next;
}ST;
//#define ST struct student
#define Len sizeof(ST)

void main(){
	ST *create(int);
	void print(ST *);
	ST *combine(ST *,ST *);
	ST *head1,*head2,*head;//head1,head2 is not a exact address value.
	head1 = create(1);
	printf("Print chain table 1:\n");
	print(head1);
	
	head2 = create(0);
	printf("\nPrint chain table 2:\n");
	print(head2);
	printf("\nPrint the order and combine table:\n");
	head = combine(head1,head2);
	print(head);
}

ST *combine(ST *head1,ST *head2){
	ST *head,*p1;
	ST *first;//head pointer to the ordered chain table.
	ST *tail;//tail pointer to the ordered chain table.
	ST *p_min;//store the font node of min pointer.
	ST *min;//store the min pointer.
	ST *p;//current compared node.
	p1 = head1;
	while(p1->next!=NULL){
		p1 = p1->next;
	}
	p1->next = head2;//combine head1 and head2
	head = head1;//combined chain table address.
	//return head;
	//chain table order from small to large
	first = NULL;
	while(head){//find the min node.
		min = head;
		p = head;
		//show the selection order thought.
		while(p->next){
			//search the min node.if it is lower than the current min node.
			if(p->next->num < min->num){
				p_min = p;//store the font node of the min pointer
				min = p->next;//store the min node.
			}
			p = p->next;
		}
		
		//now put the min in to the ordered chain table.
		if(first==NULL){
			first = min;//first of searched node.
			tail = min;//tail pointer to the last node.
		}else{
			tail->next = min;//put the min node at the last.
			tail = min;//tail pointer the min node,for chainning.
		}
		
		//check whether the min node will be delete from the previous table,head.
		if(min==head){
			head = head->next;
		}else{
			p_min->next = min->next;
		}
	}
	//when loop end,get the ordered chain table.
	if(first!=NULL) tail->next = NULL;//the last chain table point to NULL.
	head = first;//head point to the ordered chain table.
	return head;
}

ST *create(int n){
	ST *head,*p1,*p2;
	if(n){
		p1 = (ST *)malloc(Len);//notice the type change.
		head = p2 = p1;
		p1->num = 101;
		p1->score = 89.5;
		p1 = (ST*)malloc(Len);
		p1->num = 105;
		p1->score = 90.5;
		p2->next = p1;
		
		p2 = p1;
		p2->next = NULL;
	}else{
		p1 = (ST *)malloc(Len);
		head = p2 = p1;
		p1->num = 103;
		p1->score = 90.5;
		
		p1 = (ST *)malloc(Len);
		p1->num = 107;
		p1->score = 98.5;
		p2->next = p1;
		p2 = p1;
		
		p1 = (ST *)malloc(Len);
		p1->num = 104;
		p1->score = 70.5;
		p2->next = p1;
		
		p2 = p1;
		p2->next = NULL;
	}
	return head;
}

void print(ST *head){
	ST *p=head;
	while(p){
		printf("%ld %f\n",p->num,p->score);
		p = p->next;
	}
}
