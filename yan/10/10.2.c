/*
* 数据结构C语言版 表插入排序
* 算法10.3 P267-P270
* 日期：2012-08-12
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

//静态链表类型
#define SIZE 100 //静态链表容量
typedef int KeyType;//定义关键字类型为整型
typedef int InfoType;//定义其他信息的类型

typedef struct{
	KeyType key;//关键字项
	InfoType otherinfo;//其他数据项，具体类型在主程中定义
}RedType;//记录类型

typedef struct{
	RedType rc;//记录项
	int next;//指针项
}SLNode;//表结点类型

typedef struct{
	SLNode r[SIZE];//0号单元为表头结点
	int length;//链表当前长度
}SLinkListType;//静态链表类型

//由数组D建立n个元素的表插入排序的静态链表SL
void TableInsert(SLinkListType *SL,RedType D[],int n){
	int i,p,q;
	//表头结点记录的关键字取最大整数(非降序链表的表尾)
	SL->r[0].rc.key = INT_MAX;//数据最大值
	SL->r[0].next = 0;//next域为0表示表尾(现为空表，初始化)
	for(i=0;i<n;i++){
		SL->r[i+1].rc = D[i];//将数组D的值赋给静态链表SL
		q = 0;//当前数组索引
		p = SL->r[0].next;//指针项，数组的下一个链表索引项
		//静态链表向后移
		while(SL->r[p].rc.key<=SL->r[i+1].rc.key){//指针0所指向的键小于刚插入的值
			q = p;//指针p赋给q
			p = SL->r[p].next;//得到下一个指针
		}
		SL->r[i+1].next = p;//将当前记录插入静态链表，指针指向比它大的索引项
		SL->r[q].next = i+1;//q项比新插入结点小，改变q项指针指向新插入的结点
	}
	SL->length = n;
}

//算法10.3 P270
//根据静态链表SL中各结点的指针值调整记录位置，使得SL中记录按关键字非递减有序顺序排列
void Arrange(SLinkListType *SL){
	int i,p,q;//p类似指针
	SLNode t;
	p=(*SL).r[0].next;//p指示第一个记录的当前位置
	//SL->r[1..i-1]中记录已按关键字有序排列，第i个记录在SL中的当前位置应不小于i
	for(i=1;i<SL->length;i++){
		//找到第i个记录，并用p指示其在SL中当前位置
		while(p<i){
			p = SL->r[p].next;//从已经调整的记录指针找到索引项
		}
		q = SL->r[p].next;//q指示尚未调整的表尾
		//if(i==2){printf("%d,%d\n",p,q);exit(0);}//用作调试
		if(p!=i){
			//交换记录，使第i个记录到位
			t = SL->r[p];
			SL->r[p] = SL->r[i];
			SL->r[i] = t;
			//指向被移走的记录，使得以后可由while循环找回
			SL->r[i].next = p;
		}
		p = q;//p指示尚未调整的表尾，为找第i+1个记录作准备
	}
}

//求得adr[1..L.length]，adr[i]为静态链表L的第i个最小记录的序号
void Sort(SLinkListType L,int adr[]){
	int i=1,p=L.r[0].next;
	while(p){
		adr[i++] = p;
		p = L.r[p].next;
	}
}

//算法10.18(L的类型有变) P290
//adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。
//本算法按adr重排L.r，使其有序。
void Rearrange(SLinkListType *L,int adr[]){
	int i,j,k,m,n=0;
	for(i=1;i<L->length;i++){
		if(adr[i]!=i){//如果adr[i]恰为第i个最小关键字记录，该位置上的记录不需要调整
			j = i;
			L->r[0] = L->r[i];//暂存记录L->r[i]
			//调整L->r[adr[j]]的记录到位置到adr[j]=i为止
			m = 0;
			while(adr[j]!=i){
				k = adr[j];//j位置放置的是第k个最小关键字记录
				L->r[j] = L->r[k];//将
				adr[j] = j;//表示adr[j]为第j个最小关键字记录
				j = k;//记录按序到位
				m++;
			}
			//printf("m=%d",m);exit(0);
			L->r[j] = L->r[0];
			adr[j] = j;
			n++;
		}
	}
	printf("n=%d\n",n);
}

void print(SLinkListType L){
	int i;
	for(i=1;i<=L.length;i++){//按照数组索引顺序，而非指针
		printf("key=%d ord=%d next=%d\n",L.r[i].rc.key,L.r[i].rc.otherinfo,L.r[i].next);
	}
}

#define N 8

void main(){
	RedType d[N] = {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
	SLinkListType list1,list2;
	int *adr,i;
	
	TableInsert(&list1,d,N);//数据插入
	list2 = list1;//复制静态链表list2与list2相同
	printf("Before order list1:\n");
	print(list1);
	
	Arrange(&list1);//根据链表结点指针调整记录位置
	printf("\nAfter order list1:\n");
	print(list1);
	
	printf("\nBefore order list2:\n");
	print(list2);
	
	adr = (int*)malloc((list2.length+1)*sizeof(int));
	Sort(list2,adr);//用到了next值
	printf("\nThe order list2 index order by key asc:\n");//键值从小到大排列，列出键值对应的序号
	for(i=1;i<=list2.length;i++)
		printf("adr[%d]=%d ",i,adr[i]);
	printf("\n");
	
	Rearrange(&list2,adr);//没有用到next值
	printf("After list2 order:\n");
	print(list2);
}











