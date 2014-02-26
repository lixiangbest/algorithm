/***********声明部分***************/
//单循环链表
#include<stdio.h> //输入输出函数头文件
#include<stdlib.h> //内存申请函数头文件

#define false 0
#define true 1
#define ERROR false //异常抛出返回值
#define INFEASIBLE false //异常抛出返回值
#define NL "\n" //格式化输出函数
#define F "%d "
#define D "%f "
#define DL D NL

typedef float elemType;//别名声明，其实int可以用任意的数据类型代入

/*结构体定义部分*/
typedef struct CNode{//circle node
	elemType data;//数据域
	struct CNode *next;//指针域
}CN,*Link;
#define Len sizeof(CN) //*Link = CN

/*函数声明区域*/
Link initList();//构造一个空的带头结点的单循环链表L
int listLength(Link);//返回L中数据元素的个数
void listInsert(Link,int i,elemType);//在L的第i个位置之前插入元素e
elemType listDelete(Link,int i);//删除第i个元素
void listAppend(Link,elemType);//在表尾插入元素
void listOut(Link);//输出链表

/*构造一个空的带头结点的单循环链表L*/
Link initList(){
	/*操作结果：构造一个空的线性表L*/
	Link L;
	L = (Link)malloc(Len);//产生头结点，并使L指向此头结点
	if(!L){//存储分配失败
		exit(false);
	}
	L->data=0;//表头存储长度
	L->next = L;//指针域指向头结点
	return L;
}

//返回L中数据元素的个数
int listLength(Link L){
	int i=0;
	Link p=L->next;//p指向第一个元素结点
	while(p!=L){//没到表尾
		i++;
		p=p->next;
	}
	return i;
}

//在L的第i个位置之前插入元素e
void listInsert(Link L,int i,elemType e){//L带头结点，i从1开始
	Link p=L,s;//p指向头结点
	int j=0;
	if(i<=0||i>listLength(L)+1) return;
	while(j<i-1){//移动i-1位
		p = p->next;
		j++;
	}
	printf("\n%f\n",p->data);
	s = (Link)malloc(Len);//生成新结点
	s->data = e;//插入L中
	s->next = p->next;
	p->next = s;
	L->data++;//长度加1
}

//删除第i个元素，并由e返回其值
elemType listDelete(Link L,int i){
	Link p=L,q;//p指向头结点
	elemType e;
	int j=0;
	//第i个元素不存在
	if(i<=0||i>listLength(L)) return false;
	while(j<i-1){//寻找第i-1个结点
		p = p->next;
		j++;
	}
	q = p->next;//q指向待删除的节点
	p->next = q->next;
	e = q->data;
	free(q);//释放待删除结点
	L->data--;//长度减1
	return e;
}

//输出链表
void listOut(Link L){
	Link p = L->next;
	while(p!=L){
		printf(D,p->data);
		p = p->next;
	}
}

//在表尾插入元素
void listAppend(Link L,elemType e){
	Link s,p=L;
	s = (Link)malloc(Len);
	s->data = e;
	while(p->next!=L){
		if(p->next->data > e){
			break;
		}
		p = p->next;
	}
	s->next = p->next;
	p->next = s;
	L->data++;
}

#define N 3

void main(){
	int i;
	Link L = initList();
	elemType arr[N]={12,15,9},e=8;
	for(i=0;i<N;i++){
		listAppend(L,arr[i]);
	}
	//输出插入的链表元素
	printf("List length:%d\n",listLength(L));
	listOut(L);
	
	//在第i个元素前面插入值
	printf("\n\nList insert:%d element "DL,i,e);
	listInsert(L,i,e);
	listOut(L);
	
	//删除第i-1元素
	printf("\n\nList delete:%d element "DL,i-1,listDelete(L,i-1));
	printf("Length is %d\n",listLength(L));
	listOut(L);
}

