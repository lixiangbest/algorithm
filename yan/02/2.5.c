/***********声明部分***************/
//双向链表
#include<stdio.h> //输入输出函数头文件
#include<stdlib.h> //内存申请函数头文件

#define false 0
#define true 1
#define error 0
#define NL "\n" //格式化输出函数
#define F "%d "
#define D "%-4.1f "
#define DL D NL

typedef float elemType;//别名声明，其实int可以用任意的数据类型代入

/*结构体定义部分:线性表的双向链表存储结构*/
typedef struct dNode{//circle node
	elemType data;//数据域
	struct dNode *prior,*next;//指针域
}DN,*dLink;
#define Len sizeof(DN) //*Link = CN

/*函数声明区域*/
dLink initList();//构造一个空的带头结点的单循环链表
void destoryList(dLink);//销毁双向循环链表
void clearList(dLink);//将双向循环链表置空
int listEmpty(dLink);//检查链表是否为空
int listLength(dLink);//返回链表中数据元素的个数
elemType getElem(dLink,int);//返回第i个结点对应的元素值
elemType priorElem(dLink,elemType);//返回数据元素对应的前驱元素
elemType nextElem(dLink,elemType);//返回数据元素对应的后驱元素
dLink getElemPt(dLink,int);//返回第i个元素的结点地址
void listInsert(dLink,int i,elemType);//在L的第i个位置之前插入元素e
elemType listDelete(dLink,int i);//删除第i个元素
void listAppend(dLink,elemType);//在表尾插入元素
void listOut(dLink);//输出链表

/*带头结点的双向循环链表的初始化*/
dLink initList(){
	//产生空的双向循环链表
	dLink L;
	L = (dLink)malloc(Len);
	if(L){
		L->next = L->prior = L;
	}else exit(error);
}

/*销毁双向循环链表L*/
void destoryList(dLink L){
	dLink q,p=L->next;//p指向第一个结点
	while(p!=L){//p没到表头
		q = p->next;
		free(p);
		p = q;
	}
	free(L);//销毁头结点
	L = NULL;
	//printf("\n\nList is: %d\n",L);//L的值不变，L指向的地址为0
}

/*将双向循环链表置空*/
void clearList(dLink L){
	/*初始条件：L已存在。操作结果：将L重置为空表*/
	dLink q,p=L->next;//p指向第一个结点
	//p没到表头
	while(p!=L){
		q = p->next;
		free(p);
		p=q;
	}
	L->next=L->prior=L;//头结点的两个指针域均指向自身
}

/*检查链表是否为空，若为空，则返回true，否则返回false*/
int listEmpty(dLink L){
	if(L->next==L&&L->prior==L) return true;
	else return false;
}

/*返回链表中数据元素的个数*/
int listLength(dLink L){
	int i=0;
	//p指向第一个结点
	dLink p=L->next;
	/*p没到表头*/
	while(p!=L){
		i++;
		p=p->next;
	}
	return i;
}

/*返回第i个结点对应的元素值*/
elemType getElem(dLink L,int i){
	//当第i个元素存在时，返回其值，否则返回error
	int j=1;//j为计数器
	dLink p=L->next;//p指向第一个结点
	while(p!=L&&j<i){
		j++;
		p=p->next;
	}
	//第i个元素不存在
	if(p==L||j>i) return error;
	return p->data;
}

/*返回数据元素对应的前驱元素*/
elemType priorElem(dLink L,elemType e){
	//如果e是L的数据元素，且不是第一个，则返回它的前驱元素
	//否则操作失败
	dLink p=L->next->next;//p指向第2个元素
	while(p!=L){//p没到表头
		if(p->data==e){
			e = p->prior->data;//定义前驱结点的好处在此
			return e;
		}
		p=p->next;
	}
	return false;//没有找到
}

/*返回数据元素对应的后驱元素*/
elemType nextElem(dLink L,elemType e){
	//如果e是L的数据元素，且不是最后一个，则返回它的前驱元素
	//否则操作失败
	dLink p=L->next->next;//p指向第2个元素
	while(p!=L){//p没到表头
		if(p->prior->data==e){
			return p->data;
		}
		p = p->next;
	}
	return false;
}

/*返回第i个元素的结点地址*/
dLink getElemPt(dLink L,int i){
	//在双向链表L中返回第i个元素的地址。i为0返回头结点的地址
	//若第i个元素不存在，返回NULL
	int j;
	dLink p=L;//p指向头结点
	//i值不合法
	if(i<0||i>listLength(L)){
		return NULL;
	}
	for(j=1;j<=i;j++) p=p->next;
	return p;
}

/*在L的第i个位置之前插入元素e*/
void listInsert(dLink L,int i,elemType e){
	//i的合法值为1<=i<=表长+1
	//i=表长+1时，前驱为第i=表长元素
	dLink p,s;
	//i值不合法
	if(i<1||i>listLength(L)+1) return;
	p = getElemPt(L,i-1);//在L中确定第i个元素前驱的位置指针p
	//p=NULL,即第i个元素的前驱不存在(设头结点为第1个元素的前驱)
	if(!p) return;
	s = (dLink)malloc(Len);
	if(!s) return;
	s->data = e;
	s->prior = p;//在第i-1个元素之后插入
	s->next = p->next;
	p->next->prior = s;//以前的p->next->prior==p
	p->next = s;
}

/*删除第i个元素*/
elemType listDelete(dLink L,int i){
	//在带头结点的双链循环线性表L中第i个位置之前插入元素e，
	//i的合法值为1<=i<=表长
	dLink p;
	elemType e;
	//i值不合法
	if(i<1) return error;
	p = getElemPt(L,i);//在L中确定第i个元素的位置指针p
	//p=NULL,即第i个元素不存在
	if(!p) return error;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return e;
}

//输出链表
void listOut(dLink L){
	dLink p = L->next;//指向第一个结点
	while(p!=L){
		printf(D,p->data);
		p = p->next;
	}
}

#define N 5
void main(){
	elemType arr[N] = {2,8,3,5,1},e;
	int i;
	dLink L;
	L = initList();
	for(i=0;i<N;i++){
		listInsert(L,i+1,arr[i]);
	}
	printf("The double list length is:%d\n",listLength(L));
	listOut(L);
	//获得第i个元素的值
	e=getElem(L,i);
	printf("\n\nget the %d value is "DL,i,e);
	//获得第i个元素之前的元素值
	printf("\n\nbefore the "D"value is "DL,e,priorElem(L,e));
	//获得第i个元素之后的元素值
	printf("\n\nafter the "D"value is "DL,e,nextElem(L,e));//not found
	//删除第3个元素
	printf("\n\ndelete the %d value is "DL,i,listDelete(L,i));
	listOut(L);
	//清空表
	if(!listEmpty(L)){
		clearList(L);//置空
	}
	printf("\n\nafter clear the list length: %d",listLength(L));
	listOut(L);//out empty.
	//删除表
	destoryList(L);
	if(L==NULL)
		printf("\n\nList is: %d",*L);//L的值不变，L指向的地址不为空，是一个不确定的值
}

