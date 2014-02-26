/*
	数据结构C语言版 次优查找树
	P223
	日期：2012年7月29日
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 9 //数据元素个数

typedef char keyType;//设关键字域为字符型

typedef struct{
	keyType key;//关键字
	int weight;//权值
}elemType;

// 静态查找表的顺序存储结构
typedef struct{
	// 数据元素存储空间基址，建表时按实际长度分配，0号单元留空
	elemType *elem;
	int length;//表长度
}ssTable;

elemType r[N]={
	{'A',1},{'B',1},{'C',2},{'D',5},{'E',3},
	{'F',4},{'G',4},{'H',3},{'I',5}
}; // 数据元素(以教科书例9-1为例),全局变量

int sw[N+1];//累计权值，全局变量

typedef elemType TElemType;

//二叉树的二叉链表存储表示
typedef struct biTNode{
	TElemType data;//数据域
	struct biTNode *lchild,*rchild;//左右孩子指针
}biTNode,*biTree;

//创建查询树表
int create_seq(ssTable *ST,int n){
	int i;
	ST->elem = (elemType*)calloc(n+1,sizeof(elemType));//动态生成n+1个数据元素空间(0号单元不用)
	if(!ST->elem) return 0;
	for(i=1;i<=n;i++){
		*(ST->elem+i) = r[i-1];//将全局数组r的值一次赋给ST
	}
	ST->length = n;
	return 1;
}

// 创建静态查找表为按关键字非降序排序
void ascend(ssTable *ST){
	int i,j,k;
	for(i=1;i<ST->length;i++){
		k = i;
		ST->elem[0] = ST->elem[i];//待比较值存[0]单元
		for(j=i+1;j<=ST->length;j++){
			if(ST->elem[j].key < ST->elem[0].key){
				k = j;
				ST->elem[0] = ST->elem[j];
			}
		}
		//有更小的值则交换
		if(k!=i){
			ST->elem[k] = ST->elem[i];
			ST->elem[i] = ST->elem[0];//此时存储的值相对所有比较值而言为最小
		}
	}
}

// 构造一个含n个数据元素的按关键字非降序查找表ST，数据来自全局数组r。
int create_ord(ssTable *ST,int n){
	int f;
	f = create_seq(ST,n);
	if(f) ascend(ST);
	return f;
}

// 销毁表ST
int destroy(ssTable *ST){
	free(ST->elem);
	ST->elem = NULL;
	ST->length = 0;
	return 1;
}

// 按照有序表ST中各数据元素的weight求累计权值表sw
void findSW(int sw[],ssTable ST){
	int i;
	sw[0] = 0;
	//s[i]表示i前面所有元素的权值之和包括i在内
	for(i=1;i<=ST.length;i++)
		sw[i] = sw[i-1]+ST.elem[i].weight;
}

// 算法9.3 P223
// 由有序表R[low..high]及其累计权值表sw(其中sw[0]==0)递归构造次优查找树T
int secondOptimal(biTree *T,elemType R[],int sw[],int low,int high){
	int i,j;
	double min,dw;
	i = low;
	min = fabs(sw[high]-sw[low]);//fabs函数求绝对值
	dw = sw[high]+sw[low-1];
	//选择最小的△Pi的值
	for(j=low+1;j<=high;j++){
		if(abs(dw-sw[j]-sw[j-1])<min){
			i = j;
			min = fabs(dw-sw[j]-sw[j-1]);
		}
	}
	*T = (biTree)malloc(sizeof(biTNode));
	if(!*T) return 0;
	(*T)->data = R[i];//生成结点
	if(i==low) (*T)->lchild = NULL;//左子树为空
	else secondOptimal(&(*T)->lchild,R,sw,low,i-1);//构造左子树
	if(i==high) (*T)->rchild = NULL;//右子树为空
	else secondOptimal(&(*T)->rchild,R,sw,i+1,high);//构造右子树
	return 1;
}

typedef biTree SOSTree;//次优查找树采用二叉链表的存储结构
// 算法9.4 P225
// 由有序表ST构造一棵次优查找树T。ST的数据元素含有权域weight。
int createSOSTree(SOSTree *T,ssTable ST){
	if(ST.length==0) *T = NULL;
	else{
		findSW(sw,ST);//按照有序表ST中各数据元素的Weight域求累计权值表sw
		secondOptimal(T,ST.elem,sw,1,ST.length);//构造次优查找树
	}
	return 1;
}

// 在次优查找树T中查找关键字等于key的元素。找到则返回1，否则返回0
int searchSOSTree(SOSTree *T,keyType key){
	int times = 0;
	while(*T){//T非空
		times++;
		if((*T)->data.key == key){
			printf("Compares times:%d\n",times);
			return 1;
		}else if((*T)->data.key>key) *T = (*T)->lchild;
		else *T = (*T)->rchild;
	}
	printf("Compares times:%d\n",times);
	return 0;
}

// 次优查找树T的遍历(先序遍历)
void traverseSOSTree(SOSTree T,void(*visit)(elemType)){
	if(T){
		(*visit)(T->data);
	}else printf("  ");
	if(T->lchild) traverseSOSTree(T->lchild,visit);//左子树
	if(T->rchild) traverseSOSTree(T->rchild,visit);//右子树
}

// 按顺序对ST的每个元素调用函数visit()一次
int traverse(ssTable ST,void(*visit)(elemType)){
	elemType *p;
	int i;
	p = ++ST.elem;//p指向第一个元素，第0个元素没有用
	for(i=1;i<=ST.length;i++)
		(*visit)(*p++);
	return 1;
}

// traverse()调用的函数
void print(elemType c){
	printf("('%c' %d)",c.key,c.weight);
}

void main(){
	ssTable st;//静态查找表
	SOSTree t;//次优查找树
	int i;
	keyType s;
	printf("print the ssTable:\n");
	create_ord(&st,N);//由全局数组产生非降序静态查找表st
	traverse(st,print);
	
	printf("\n\nprint the SOSTree:\n");
	createSOSTree(&t,st);//由有序表构造一棵次优查找树
	traverseSOSTree(t,print);//次优查找树遍历
	printf("\nplease enter the char for search:\n");
	scanf("%c",&s);
	i = searchSOSTree(&t,s);
	if(i) printf("\nThe weight of '%c' is %d\n",s,t->data.weight);
	else printf("\nNot found\n");
}

