#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 5
typedef struct student{
	long num;
	char name[30];
	struct student *next;
}STU,*Stu;

#define Len sizeof(STU)

void main(){
	Stu create();//create link table.
	void print(Stu head);//output link table.
	Stu delete(Stu head);//create link table.
	Stu select_sort(Stu head);//order by selecting.
	Stu insert_sort(Stu head);//order by inserting.
	Stu bubble_sort(Stu head);//order by bubbling.
	Stu reverse(Stu head);//reverse the link table.
	Stu insert(Stu head);//reverse the link table.
	Stu head;
	//step to create link table.
	printf("The link table after creating:\n");
	head = create();
	print(head);
	
	//step to delete an element from link table.
	//printf("\nThe link table after deleting:\n");
	//head = delete(head);
	//print(head);
	
	//reverse the link table.
	printf("\nThe link table after reversing:\n");
	//head = reverse(head);
	print(head);
	
	/*
	//select sort.
	printf("\norder by selecting from min to max.\n");
	head = select_sort(head);
	print(head);
	
	//insert sort.
	printf("\norder by inserting from min to max.\n");
	head = insert_sort(head);
	print(head);
	
	//insert a value to the ordered link table.
	printf("\ninsert a value to the ordered link table.\n");
	head = insert(head);
	print(head);
	*/
	
	//bubble sort.
	printf("\norder by bubbling from min to max.\n");
	head = bubble_sort(head);
	print(head);
}

//order by bubbling from min to max
Stu bubble_sort(Stu head){
	Stu p_start;//store the current operating element.
	Stu p;//store the tmp pointer.
	Stu p_tmp;//store the font of current operating element.
	Stu p_end=NULL;//the end of second bubble.
	//notice the bubble times.
	p_start = (Stu)malloc(Len);
	p_start->next = head;
	head = p_start;
	while(head!=p_end){
		p = p_start = head;
		while(p_start->next->next!=p_end){
			if(p_start->next->num > p_start->next->next->num){
				p_tmp = p_start->next->next;
				p_start->next->next = p_tmp->next;
				p_tmp->next = p_start->next;
				p_start->next = p_tmp;
				p = p_start->next->next;
			}
			p_start = p_start->next;
		}
		p_end = p;
	}
	p_start = head;
	head = head->next;
	free(p_start);
	/*
	for(p_start=head,p_before=p_start,p_end=NULL;p->next!=p_end;p=p->next){
		for(p=p_start->next;p!=NULL;p=p->next){
			if(p_before->num > p->num){//exchange
				if(p_before==head) head = p;//change the head of link table.
				p_rest = p->next;
				p_before->next = p_rest;
				p->next = p_before;
				//let p be the next node.
				p_end = p;
				p = p->next;
			}else{
				p_end = p_before;
				p_before = p;
			}
		}
	}*/
	return head;
}

//order by inserting from min to max.
Stu insert_sort(Stu head){
	Stu p_insert;//new link table which other nodes will insert into.
	Stu p_before;//the font of new link table node.
	Stu p = head->next;//store the current operating node.
	Stu p_next;//store the next node of p;
	head->next = NULL;
	for(;p!=NULL;p=p_next){
		p_next = p->next;//the following code will overload the p->next;
		p_before = head;
		p_insert = head;
		while(p_insert!=NULL){
			if(p->num <= p_insert->num){
				break;
			}
			p_before = p_insert;
			p_insert = p_insert->next;
		}
		if(p_insert == head){//or head->num >= p->num
			head = p;
			//p->next = p_before;//p_before = p_insert = head.
		}else{
			//p->next = p_before->next;//p_before->next = p_insert.
			p_before->next = p;
		}
		p->next = p_insert;
		//printf("\n%d\n",head->num);
		//exit(0);
	}
	return head;
}

//order by selecting from min to max.
Stu select_sort(Stu head){
	Stu new_head=NULL;//new head of the link table.
	Stu new_tail=NULL;//new tail of the link table.
	Stu p;//firt loop link table.
	Stu pn;//second loop link table.
	Stu t_before;//the font node of the current min node in the loop.
	Stu t_p;//the current node in first loop.
	//select sort algorithm.
	for(p=head;p!=NULL;p=head){
		t_p = p;
		//printf("\np %d\n",t_p->num);
		for(t_before=p,pn=p;pn->next!=NULL;pn=pn->next){
			if(pn->next->num <= t_p->num){
				t_p = pn->next;
				t_before = pn;
			}
		}
		//check the current p node whether is the min node.
		if(t_p==p){
			head = head->next;
		}else{
			//delete the min node.
			t_before->next = t_p->next;
		}
		//if the first insert to the new link table.
		if(new_head==NULL){
			new_head = new_tail = t_p;
			new_tail->next = NULL;
		}else{
			new_tail->next = t_p;
			new_tail = t_p;
			new_tail->next = NULL;
		}
	}
	head = new_head;
	return head;
}

//insert a value to the ordered link table.
Stu insert(Stu head){
	Stu p=head;
	Stu p_before=head;//store the before of current node.
	Stu new = malloc(Len);//the inserted node.
	new->num = 10045;
	strcpy(new->name,"Li neng");
	while(p!=NULL){
		if(p->num >= new->num){
			break;
		}
		p_before = p;
		p = p->next;
	}
	//insert new node to the head.
	if(head->num >= new->num){
		head = new;
		new->next = p;
	}else{
		new->next = p;
		p_before->next = new;
	}
	return head;
}

//reverse the link table.
Stu reverse(Stu head){
	Stu p=head->next;//current operation node.
	Stu p_before=head;//store the before node of current node.
	Stu p_next;//store the next link table.
	head->next = NULL;
	while(p!=NULL){
		p_next = p->next;
		p->next = p_before;
		p_before = p;
		p = p_next;//loop condition
	}
	head = p_before;
	return head;
}

//delete an element from link table.
Stu delete(Stu head){
	long num;//the num of deleted elment
	Stu p,pbefore;
	printf("Enter the num of student you want to be delete:\n");
	scanf("%ld",&num);
	p = pbefore = head;
	while(p){
		if(p->num != num){
			pbefore = p;
		}else break;
		p = p->next;
	}
	if(p==NULL) printf("num does not found!\n");
	else if(pbefore==head){//num is the first element.
		head = head->next;
		free(pbefore);
	}else{
		pbefore->next = p->next;
		free(p);
	}
	return head;
}

//create link table.
Stu create(){
	Stu head,p1,p2;
	long num[N] = {10031,10044,10021,10025,10027};//student number 10022 to 10046
	char *name[N] = {"Zheng bing","Li xiang","Fang rong","Jun hui","Bao an"};
	int i;
	//assign the value to the link table.
	for(i=0;i<N;i++){
		p1 = (Stu)malloc(Len);
		if(i==0) head = p2 = p1;
		else{
			p2->next = p1;
			p2 = p1;
		}
		p1->num = num[i];
		strcpy(p1->name,name[i]);
	}
	p2->next = NULL;
	return head;
}

void print(Stu head){
	Stu p=head;
	while(p){
		printf("Num:%-15d Name:%-15s\n", p->num, p->name);
		p = p->next;
	}
}