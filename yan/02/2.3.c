/***********声明部分***************/
#include<stdio.h> //输入输出函数头文件
#include<stdlib.h> //内存申请函数头文件

#define false 0
#define true 1
#define N 5
#define Max_size 8 //定义最初申请的数值的大小
#define ERROR false //异常抛出返回值
#define INFEASIBLE false //异常抛出返回值
#define NL "\n" //格式化输出函数
#define F "%f "
#define D "%d "
#define DL D NL

typedef int elemType;//别名声明，其实int可以用任意的数据类型代入

/*结构体定义部分*/
typedef struct{
	elemType data;//数据域
	int cur;//指针域
}*sLink,Link[Max_size];//结构体数组

/*函数声明区域*/
void initList(sLink L);//构造一个空的带头结点的线性链表L
void clearList(sLink L);//将已存在的线性表清空
int listEmpty(sLink L);//若L为空表，返回TRUE；否则返回FALSE
int listLength(sLink L);//返回L中数据元素的个数
int mallocList(sLink L);//申请建立一个结点
void freeList(sLink L,int k);//将下标为k的空闲结点收回到备用链表
void listInsert(sLink L,int i,elemType e);//在L中第i个元素之前插入新的数据元素e
elemType listDelete(sLink L,int i);//在L中删除第i个元素并返回其值
void appendList(sLink L,elemType e);//在当前链表后面插入元素
void outList(sLink L);//输出链表L
int locateElem(sLink L,elemType e);//在静态链表中查找第1个值为e的元素。若找到，则返回它在L中的位序，否则返回0

/*静态链表初始化*/
void initList(sLink L){
	//构造一个空的链表，表头为L的最后一个单元L[Max_size-1]，
	//其余单元链成一个备用链表，表头为L的第一个单元L[0]，0表示空指针
	//注意空链表表头和备用链表表头的区别即位置
	int i;
	L[Max_size-1].cur = 0;//L的最后一个单位为空链表的表头
	//将其余单元链接成以L[0]为表头的备用链表
	for(i=0;i<Max_size-2;i++) L[i].cur = i+1;
	L[Max_size-2].cur = 0;
}

/*清空静态链表*/
void clearList(sLink L){
	/*初始条件：线性表L已存在。操作结果：将L重置为空表*/
	int i,j,k;
	i = L[Max_size-1].cur;//内容链表第一个结点的位置
	L[Max_size-1].cur = 0;//内容链表为空
	k = L[0].cur;//备用链表第一个结点的位置
	L[0].cur = i;//备份链表的表头链接到链表的第一个结点
	while(i){//没到链表尾
		j = i;
		//printf("\nj=%d\n",j);
		i = L[i].cur;//指向下一个元素
	}
	//printf("\nj=%d\n",j);
	L[j].cur = k;//原内容链表的表尾(为0)接到原备用链表的第一个结点
}

/*判断L是否为空表*/
int listEmpty(sLink L){
	/*若L是空表，返回TRUE;否则返回FALSE*/
	if(L[Max_size-1].cur == 0){//空表
		return true;
	}else return false;
}

/*返回L中数据元素的个数*/
int listLength(sLink L){
	int j=0,i=L[Max_size-1].cur;//i指向第一个元素
	while(i){//没到静态链表尾
		i = L[i].cur;//指向下一个元素
		j++;
	}
	return j;
}

/*申请建立一个结点*/
int mallocList(sLink L){
	//若备用空间链表为空，则返回分配的结点下标，否则返回0
	int i = L[0].cur;//备用链表的头指针
	if(i){
		L[0].cur = L[i].cur;
	}
	return i;
}

/*将下标为k的空闲结点收回到备用链表,下一次分配时从k开始*/
void freeList(sLink L,int k){
	L[k].cur = L[0].cur;
	L[0].cur = k;
}

/*在L中第i个元素之前插入新的数据元素e*/
void listInsert(sLink L,int i,elemType e){
	/*在L中第i个元素之前插入新的数据元素e*/
	int d,j,k = Max_size-1;//k指向表头
	if(i<1||i>listLength(L)+1) return;
	j = mallocList(L);//申请新单元
	/*申请成功*/
	if(j){
		L[j].data = e;//赋值给新单元
		for(d=1;d<i;d++){//移动i-1个元素
			k = L[k].cur;
		}
		L[j].cur = L[k].cur;//指向第i个元素
		L[k].cur = j;//以前的第i-1个元素指向当前的e元素所在位置
	}
}

/*在L中删除第i个元素并返回其值*/
elemType listDelete(sLink L,int i){
	int j,k=Max_size-1;//指向内容链表表头
	if(i<1||i>listLength(L)) return false;
	for(j=1;j<i;j++) k = L[k].cur;//移动i-1个元素
	j = L[k].cur;//第i-1个元素指向的结点
	L[k].cur = L[j].cur;//第i个元素指向的结点
	freeList(L,j);
	return L[j].data;
}

/*在当前链表后面插入元素*/
void appendList(sLink L,elemType e){
	int d,j,k = Max_size-1;//k指向表头
	if(Max_size<=listLength(L)) return;
	j = mallocList(L);//申请新单元
	//printf("\ncur=%d j=%d\n",L[0].cur,j);
	if(j){
		L[j].data = e;//赋值给新单元
		while(L[k].cur){
			k = L[k].cur;
		}
		L[k].cur = j;//指向当前插入的元素
		L[j].cur = 0;//指向表尾
	}
}

/*在静态链表中查找第1个值为e的元素。若找到，则返回它在L中的位序，否则返回0*/
int locateElem(sLink L,elemType e){
	int i = L[Max_size].cur;//i指示表中第一个节点的位置
	//在表中顺序查找(e不能使字符串)
	while(i&&L[i].data!=e){
		i = L[i].cur;
	}
	return i;
}

/*为静态链表输出数据*/
void outList(sLink L){
	int i;
	for(i=0;i<Max_size;i++) printf("val=%d cur=%d; ", L[i].data, L[i].cur);
	i = L[Max_size-1].cur;
	printf("\n\n");
	while(i){
		printf("val=%d cur=%d;",L[i].data,L[i].cur);
		i = L[i].cur;//指向下一个元素
	}
}

void main(){
	int i,e=14,location=1;
	elemType arr[N] = {5,6,7,3,9};
	Link L;
	initList(L);
	//在表尾插入元素
	for(i=0;i<N;i++) appendList(L,arr[i]);
	printf("Print the list L length %d:\n",listLength(L));
	outList(L);
	
	//在第i个元素前插入元素1<=i
	printf("\n\nPrint the list L when insert %d before %d:\n",e,location);
	listInsert(L,location,e);
	outList(L);
	
	//清空链表
	printf("\n\nAfter clear the list:\n");
	clearList(L);
	outList(L);
	
	//添加新的元素
	for(i=0;i<N;i++) appendList(L,arr[N-i-1]);
	printf("\n\nInsert to the list:\n");
	outList(L);
	
	//寻找元素的位置
	printf("\n\nFound the location of %d is %d\n",3,locateElem(L,3));
	
	//删除第i个元素
	printf("\n\nDelete the %d element:%d\n",2,listDelete(L,2));
	outList(L);
	printf("\n");
	appendList(L,3);
	outList(L);
	
	//寻找元素
	//printf("\nFind the element"D" Location %d",e,locateElem(L,e));
}
