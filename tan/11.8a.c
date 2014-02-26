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
	ST *selectSort(ST *);
	ST *insertSort(ST *);
	ST *insert_sort(ST *);
	ST *bubbleSort(ST *);
	ST *head1,*head2,*head;//head1,head2 is not a exact address value.
	head1 = create(1);
	printf("Print chain table 1:\n");
	print(head1);
	
	head2 = create(0);
	printf("\nPrint chain table 2:\n");
	print(head2);
	
	printf("\nPrint the combine table:\n");
	head = combine(head1,head2);
	print(head);
	
	printf("\nPrint the select order from max to min table:\n");
	head = selectSort(head);
	print(head);
	
	printf("\nPrint the insert 1 order from max to min table:\n");
	head = insertSort(head);
	print(head);
	
	printf("\nPrint the insert 2 order from max to min table:\n");
	head = insert_sort(head);
	print(head);
	
	printf("\nPrint the buffer order from max to min table:\n");
	head = bubbleSort(head);
	print(head);
}

ST *combine(ST *head1,ST *head2){
	ST *head,*p1;
	p1 = head1;
	while(p1->next!=NULL){
		p1 = p1->next;
	}
	p1->next = head2;//combine head1 and head2
	head = head1;//combined chain table address.
	return head;
}

//bubble sort.
ST *bubbleSort(ST *head){
	ST *endpt;//loop compared.
	ST *p;//temp
	ST *p1;
	ST *p2;
	p1 = (ST *)malloc(Len);
	p1->next = head;//add a node for compared.
	head = p1;//let head point p1.
	for(endpt=NULL;endpt!=head;endpt=p){
		for(p=p1=head;p1->next->next!=endpt;p1=p1->next){
			//if the font node is greater than the back node,then exchange.
			if(p1->next->num < p1->next->next->num){
				p2 = p1->next->next;
				p1->next->next = p2->next;
				p2->next = p1->next;
				p1->next = p2;
				//get the end.
				p = p1->next->next;
			}
		}
	}
	p1 = head;//clear the information of p1.
	head = head->next;//let head point the first node of ordered chain table.
	free(p1);
	p1 = NULL;//p1=NULL
	return head;
}

ST *selectSort(ST *head){
	ST *first;//head pointer to the ordered chain table.
	ST *tail;//tail pointer to the ordered chain table.
	ST *p_min;//store the font node of min pointer.
	ST *min;//store the min pointer.
	ST *p;//current compared node.
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

ST *insert_sort(ST *head){
	ST *first;//point the left chain table.
	ST *p;//point the new inserted node.
	ST *pos;//store the previous node.
	ST *pnext;//store the next of new inserted node.
	ST *fnext;//at the back of the inserted value.
	//chain table order from small to large.use insert order.
	p = head;
	first = head->next;
	p->next = NULL;
	//select sort.
	while(first){
		p = head;fnext = first->next;
		//insert the leaving chain table node to the head.
		while((p->num < first->num)&&(p->next!=NULL)){//check the current node value and check the next node is null.
			pos = p;//store the previous node.
			p = p->next;
		}
		//printf("\n%d\n",pos->num);
		if(p->num >= first->num){//if found the position for inserting node.
			if(p==head) head = first;
			else pos->next = first;
			first->next = p;
		}else{//if not found,has traversed the p,at the end of p.
			p->next = first;
			first->next = NULL;
		}
		first = fnext;
	}
	return head;
}

ST *insertSort(ST *head){
	ST *first;//pointer in the rest of primary table is used to insert the order table.
	ST *t;//insert node.
	ST *p;//store the previous node of the found position.
	ST *q;
	first = head->next;
	head->next = NULL;//only a node.
	while(first!=NULL){//traverse the unordered chain table.
		//show inserting a node to the order chain table.
		//find the insertint position.
		for(t=first,q=head;((q!=NULL)&&(q->num > t->num));p=q,q=q->next);
		//exit for loop,it means that has found the inserting position.
		first = first->next;//leaving the unordered chain table to the ordered chain table.
		if(q==head){//insert before the first node.
			head = t;
		}else{//p is in the font of q
			p->next = t;
		}
		t->next = q;//insert the value.
	}
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
