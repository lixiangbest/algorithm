/***********声明部分***************/
#include<stdio.h> //输入输出函数头文件
#include<stdlib.h> //内存申请函数头文件

#define false 0
#define true 1
#define Size 5 //定义最初申请的数值的大小
#define ERROR false //异常抛出返回值
#define INFEASIBLE false //异常抛出返回值
#define NL "\n" //格式化输出函数
#define F "%d "
#define D "%f "
#define DL D NL

typedef float elemType;//别名声明，其实int可以用任意的数据类型代入

/*结构体定义部分*/
typedef struct LNode{
	elemType data;//数据域
	struct LNode *next;//指针域
}LN,*Link;
#define Len sizeof(LN) //*Link = LN

/*函数声明区域*/
Link initList();//构造一个空的带头结点的线性链表L
void appendList(Link head, elemType e);//插入元素到排序链表中
void insertList(Link head, int i, elemType e);//在第i个元素之前插入新的数据元素e
elemType deleteList(Link head, int i);//删除第i个元素对应的数据元素，并返回该值
void outList(Link);//链表的输出
void mergeList(Link La, Link Lb);//归并La和Lb有序链表得到新的单链表
void sortList(Link head);//将链表从小到大排序
elemType getElem(Link head,int i);//获得第i个元素，链表索引从1开始

/*初始化函数*/
Link initList(){
	//初始条件：线性表已经存在
	Link head;//定义表头结点，head->data存放链表长度，head->next存放链表
	head = (Link)malloc(Len);
	if(!head) exit(false);
	head->data = 0;//链表初始长度为0
	head->next = NULL;//链表的尾指针为NULL
	return head;
}

/*插入链表元素*/
void appendList(Link head,elemType e){
	Link s,L=head;//新节点
	s = (Link)malloc(Len);
	s->data = e;
	while(L->next){
		if(L->next->data > e){
			break;
		}
		L = L->next;
	}
	//插入元素
	s->next = L->next;
	L->next = s;
	head->data++;//头结点长度加1
}

/*将链表从小到大排序*/
void sortList(Link head){
	Link p=head;//当前节点
	Link tmp,tmp1;//临时节点
	Link tail = NULL;//冒泡结束的节点
	for(;p->next!=tail;p=head){
		for(tmp=p;tmp->next->next!=tail;tmp=tmp->next){
			//前面节点大于后面节点，则交换
			if(tmp->next->data > tmp->next->next->data){
				tmp1 = tmp->next;
				tmp->next = tmp1->next;
				tmp1->next = tmp->next->next;
				tmp->next->next = tmp1;
			}
		}
		tail = tmp->next;
	}
}

/*归并La和Lb有序链表得到新的单链表*/
void mergeList(Link La, Link Lb){
	//已知单链表La和Lb的元素按值非递减排列
	//归并La和Lb得到新的单链表Lc，Lc的元素也按值非递减排列
	Link pa = La->next,pb = Lb->next,Lc,pc;
	Lc = pc = La;//用La的头结点作为Lc的头结点
	Lc->data = La->data + Lb->data;
	while(pa&&pb){
		//如果pa元素小于pb元素
		if(pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}else{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa?pa:pb;//插入剩余段
	Lb->next = NULL;
	free(Lb);//Lb是一个独立的头结点
}

/*输出链表元素*/
void outList(Link head){
	Link L = head;
	//判断链表是否为空
	if(!L->next){
		printf("List is empty!");
		return;
	}
	while(L->next){
		printf(D,L->next->data);
		L = L->next;
	}
}

/*在带头结点的单链表中第i个元素之前插入新的数据元素e*/
void insertList(Link head, int i, elemType e){
	//初始条件：线性表已经存在
	int j=0;
	Link p = head,s;
	//寻找第i个节点
	while(p&&j<i-1){
		p = p->next;
		j++;
	}
	//i小于1或者大于表长
	if(!p||j>i-1){
		printf("Error");
		return;
	}
	s = (Link)malloc(Len);//生成新节点
	s->data = e;//插入L中
	s->next = p->next;
	p->next = s;
	head->data++;
}

//删除第i个元素对应的数据元素，并返回该值
elemType deleteList(Link head, int i){
	elemType e;
	//初始条件：线性表已经存在，i>=1
	Link p = head,q;
	int j = 0;
	//寻找第i个结点，并令p指向其前驱
	while(p->next&&j<i-1){
		p = p->next;
		j++;
	}
	//删除位置不合理
	if(!(p->next)||j>i-1) return ERROR;
	q = p->next;p->next = q->next;//删除并释放节点
	e = q->data;
	free(q);//防止出现大量无用的节点空间
	head->data--;//长度减1
	return e;
}

/*获得第i个元素，链表索引从1开始*/
elemType getElem(Link head,int i){
	int j = 1;//初始化，p指向第一个节点，j为计数器
	Link p = head->next;
	while(p&&j<i){//顺指针向后查找，直到p指向第i个元素或p为空
		p = p->next;
		j++;
	}
	if(!p||j>i){//第i个元素不正常
		return ERROR;
	}
	return p->data;//取第i个元素
}

void main(){
	Link L1,L2;
	L1 = initList();//链表初始化
	L2 = initList();//链表初始化
	elemType arr[3] = {5,1,6};
	elemType brr[4] = {9,4,3,2};
	int i;
	for(i=0;i<3;i++){
		//L1插入元素
		appendList(L1,arr[i]);
	}
	for(i=0;i<4;i++){
		//L2插入元素
		insertList(L2,i+1,brr[i]);
	}
	//L1元素输出
	printf("The list L1 length %d"NL,(int)L1->data);
	outList(L1);
	printf("\nThe %d of list element is "D NL,3,getElem(L1,3));
	//插入元素
	insertList(L1,1,7);
	printf("\nThe list after inserted L1 length %d"NL,(int)L1->data);
	outList(L1);
	
	//删除元素
	printf("\n\nThe delete element is "D NL,deleteList(L1,1));
	printf("The list after deleted L1 length %d"NL,(int)L1->data);
	outList(L1);
	
	//冒泡排序
	printf("\n\nBubble sort the list1:\n");
	sortList(L1);
	outList(L1);
	
	//L2元素输出
	printf("\n\nThe list L2 length %d"NL,(int)L2->data);
	outList(L2);
	//冒泡排序
	printf("\n\nBubble sort the list2:\n");
	sortList(L2);
	outList(L2);
	
	//L1和L2 Merge
	printf("\n\nMerge the list1 and list2:\n");
	mergeList(L1,L2);
	outList(L1);//L1地址不变，为合并后的链表头结点
}

