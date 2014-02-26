/*--------
  二叉树(Binary Tree)的顺序存储表示和实现
  P126
  ----------------*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

typedef char elemType;

#define Max_tree_size 100 //二叉树的最大结点数

typedef elemType sqBiTree[Max_tree_size];//0号单元存储根结点

typedef struct{
	int level;//结点的层
	int order;//本层序号(按满二叉树计算)
}position;

typedef int qElemType;

//队列的顺序存储结构(可用于循环队列和非循环队列)
#define MaxQsize 5 //最大队列长度(对于循环队列，最大队列长度减1)
typedef struct{
	qElemType *base;//初始化的动态分配存储空间，相当于一个数组
	int front;//头指针，若队列不空，指向队列头元素，相当于一个数组下标
	int rear;//尾指针，若队列不空，指向队列尾元素的下一个位置,相当于一个数组下标
}sqQueue;

#define clearBiTree initBiTree //顺序存储结构中，两函数完全一样
elemType Nil = ' ';//设空为字符型的空格符

//构造空二叉树T。因为T是固定数组，不会改变，故不需要&
int initBiTree(sqBiTree T){
	int i;
	for(i=0;i<Max_tree_size;i++){
		T[i] = Nil;//初值为空
	}
	return 1;
}

void destroyBiTree(){
	//由于sqBiTree是定长类型，无法销毁
}

//按层序号输入二叉树中结点的值(字符型或整型)，构造顺序存储的二叉树T
//注意本程序按照满二叉树的编号是0,1,2,.....
//而不是本程序按照满二叉树的编号是1,2,3,.....
int createBiTree(sqBiTree T){
	int i = 0,len;
	char s[Max_tree_size];
	printf("Please enter the node value(char) order by layer,space stands for empty node,\nthe amount of node is not more than %d\n",Max_tree_size);
	printf("Example:abcdefgh\n");
	gets(s);//输入字符串
	len = strlen(s);//求字符串的长度
	for(;i<len;i++){//将字符串赋值给T
		T[i] = s[i];
		//此结点(不空)无双亲且不是根,T[(i+1)/2-1] == Nil表示T[i]无双亲
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil){
			printf("it appears the node having no parents.");
			exit(0);
		}
	}
	//将空赋值给T的后面的结点
	for(i=len;i<Max_tree_size;i++){
		T[i] = Nil;
	}
	return 1;
}

//若T为空的二叉树，则返回1，否则0
int biTreeEmpty(sqBiTree T){
	//根结点为空，则树空
	if(T[0]==Nil)
		return 1;
	else return 0;
}

//返回T的深度(注意区别度和深度)
int biTreeDepth(sqBiTree T){
	int i,j = -1;
	for(i=Max_tree_size-1;i>=0;i--){//找到最后一个结点
		if(T[i]!=Nil)
			break;
	}
	i++;//为了便于计算
	do{
		j++;
	}while(i>=pow(2,j));//i>pow(2,depth-1)&&i<=pow(2,depth)
	//特别注意这里的编号是从0开始的，而不是从1开始的
	return j;
}

//当T不空，用e返回T的根，返回1；否则返回0，e无定义
int root(sqBiTree T,elemType *e){
	//T空
	if(biTreeEmpty(T)) return 0;
	else{
		*e = T[0];
		return 1;
	}
}

//返回处于位置e(层，本层序号)的结点的值
elemType value(sqBiTree T,position e){
	//将层、本层序号转为矩阵的序号
	return T[((int)pow(2,e.level-1)-1)+(e.order-1)];
	//((int)pow(2,e.level-1)-1)为e.level的结点个数
	//(e.order-1)为本层的位置,T是从0开始的
}

//给处于位置e(层，本层序号)的结点赋新值value
int assign(sqBiTree T,position e,elemType value){
	//将层、本层序号转为矩阵的序号
	int i = (int)pow(2,e.level-1)-1+e.order-1;
	//叶子非空值但双亲为空
	if(value!=Nil&&T[(i+1)/2-1]==Nil) return 0;
	else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) 
		return 0;//双亲空值但有叶子(不空)
	T[i] = value;
	return 1;
}

//若e是T的非根结点，则返回它的双亲，否则返回“空”
elemType parent(sqBiTree T,elemType e){
	int i;
	//空树
	if(T[0]==Nil) return Nil;
	for(i=1;i<Max_tree_size;i++){
		//返回双亲结点
		if(T[i]==e) return T[(i+1)/2-1];
	}
	return Nil;//没找到e
}

//返回e的左孩子。若e无左孩子，则返回“空”
elemType leftChild(sqBiTree T,elemType e){
	int i;
	//空树
	if(T[0]==Nil) return Nil;
	for(i=0;i<Max_tree_size;i++){
		//找到e
		if(T[i]==e)	return T[i*2+1];
	}
	return Nil;//找到e
}

//返回e的右孩子。若e无右孩子，则返回“空”
elemType rightChild(sqBiTree T,elemType e){
	int i;
	//空树
	if(T[0]==Nil) return Nil;
	for(i=0;i<Max_tree_size;i++){
		//找到e
		if(T[i]==e)	return T[i*2+2];
	}
	return Nil;//找到e
}

//返回e的左兄弟。若e是T的左孩子或无左兄弟，则返回“空”
elemType leftSibling(sqBiTree T,elemType e){
	int i;
	//空树
	if(T[0]==Nil)	return Nil;
	for(i=1;i<Max_tree_size;i++)
		//找到e且其序号为偶数(是右孩子)
		if(T[i]==e&&i%2==0)	return T[i-1];
	return Nil;//没找到e
}

//返回e的右兄弟。若e是T的右孩子或无右兄弟，则返回“空”
elemType rightSibling(sqBiTree T,elemType e){
	int i;
	//空树
	if(T[0]==Nil)	return Nil;
	for(i=1;i<Max_tree_size;i++)
		//找到e且其序号为奇数(是左孩子)
		if(T[i]==e&&i%2!=0)	return T[i+1];
	return Nil;//没找到e
}

//把从q的j结点开始的子树移为从T的i结点开始的子树
//insertChild()用到
//递归调用
void move(sqBiTree q,int j,sqBiTree T,int i){
	//q的左子树不空
	if(q[2*j+1]!=Nil)
		//把q的j结点的左子树移为T的i结点的左子树
		move(q,(2*j+1),T,(2*i+1));
	//q的右子树不空
	if(q[2*j+2]!=Nil)
		//把q的j结点的右子树移为T的i结点的右子树
		move(q,(2*j+2),T,(2*i+2));
	T[i] = q[j];//把q的j结点移为T的i结点
	q[j] = Nil;//把q的j结点置为空
}

//根据LR为0或1，插入c为T中p结点的左或右子树。p结点的原有左或右子树则成为c的右子树
//0表示左子树，1表示右子树
int insertChild(sqBiTree T,elemType p,int LR,sqBiTree c){
	int j,k,i=0;
	int count = (int)pow(2,biTreeDepth(T))-1;//结点数
	//查找p的序号
	for(j=0;j<count;j++){
		//j为p的序号
		if(T[j]==p) break;
	}
	k = 2*j+1+LR;//k为p的左或右孩子的序号
	//p原来的左或右孩子不空
	if(T[k]!=Nil)
		//把从T的k结点的子树移为从k结点的右子树开始的子树
		move(T,k,T,2*k+2);
	move(c,i,T,k);//把从c的i结点开始的子树移为从T的k结点开始的子树
	return 1;
}

//构造一个空队列
int initQueue(sqQueue *Q){
	//分配定长的空间，相当于一个数组
	Q->base = (qElemType*)malloc(MaxQsize*sizeof(qElemType));
	//存储分配失败
	if(!(*Q).base)	exit(0);
	(*Q).front = (*Q).rear = 0;//初始化下标
	return 1;
}

//插入元素e为Q的新的队尾
int enQueue(sqQueue *Q,qElemType e){
	//队列满，增加1个存储单元
	if(Q->rear>=MaxQsize){
		Q->base = (qElemType*)realloc(Q->base,(Q->rear+1)*sizeof(qElemType));
		//增加单元失败
		if(!Q->base)	return 0;
	}
	*(Q->base+Q->rear) = e;
	Q->rear++;
	return 1;
}

//若队列不空，则删除Q的队头元素，用e返回其值，并返回1，否则返回0
// 队列是先进先出，栈是先进后出
int deQueue(sqQueue *Q,qElemType *e){
	//队列空
	if(Q->front==Q->rear) return 0;
	*e = Q->base[Q->front];
	Q->front = Q->front+1;
	return 1;
}

//队列输出
int printQueue(sqQueue *Q){
	int i=Q->front;
	//队列空
	if(Q->front==Q->rear) return 0;
	while(i<Q->rear){
		printf("%d ",Q->base[i]);
		i++;
	}
	return 1;
}

//根据LR为0或1，删除T中p所指结点的左或右子树
//0表示左子树，1表示右子树
int deleteChild(sqBiTree T,position p,int LR){
	int i;
	int k = 1;//队列不空的标志
	sqQueue q;
	initQueue(&q);//初始化队列，用于存放待删除的结点
	i = (int)pow(2,p.level-1)-1+p.order-1;//将层、本层序号转为矩阵的序号
	//此结点为空
	if(T[i]==Nil) return 0;
	i = i*2+1+LR;//待删除子树的左结点或右结点在矩阵中的序号
	while(k){//队列不为空，继续循环
		//左结点不空
		if(T[2*i+1]!=Nil)	enQueue(&q,2*i+1);//入队左结点的序号
		//右结点不空
		if(T[2*i+2]!=Nil)	enQueue(&q,2*i+2);//入队右结点的序号
		T[i] = Nil;//删除此结点
		k = deQueue(&q,&i);//队列不空，函数返回后i的值发生了变化
	}
	return 1;
}

int (*visitFunc)(elemType);//函数变量，即函数指针

//preOrderTraverse()调用
//注意二叉树的根结点编号从0开始的
void preTraverse(sqBiTree T,int index){
	visitFunc(T[index]);//先调用函数visitFunc处理根结点
	//左子树不空
	if(T[2*index+1]!=Nil)
		preTraverse(T,2*index+1);//然后处理左子树
	//右子树不空
	if(T[2*index+2]!=Nil)
		preTraverse(T,2*index+2);//处理右子树
}

//先序遍历T，对每个结点调用函数visit一次且仅一次
int preOrderTraverse(sqBiTree T,int(*visit)(elemType)){
	visitFunc = visit;
	//树不空
	if(!biTreeEmpty(T)){
		preTraverse(T,0);
	}
	printf("\n\n");
	return 1;
}

//inOrderTraverse()调用
void inTraverse(sqBiTree T,int index){
	//左子树不空
	if(T[2*index+1]!=Nil)
		inTraverse(T,2*index+1);
	visitFunc(T[index]);//访问左孩子
	//右子树不空
	if(T[2*index+2]!=Nil)
		inTraverse(T,2*index+2);
}

//中序遍历T，对每个结点调用函数visit一次且仅一次。
int inOrderTraverse(sqBiTree T,int(*visit)(elemType)){
	visitFunc = visit;
	//树不空
	if(!biTreeEmpty(T))	inTraverse(T,0);
	printf("\n\n");
	return 0;
}

//postOrderTraverse()调用
void postTraverse(sqBiTree T,int index){
	//左子树不空
	if(T[2*index+1]!=Nil)
		postTraverse(T,2*index+1);
	//右子树不空
	if(T[2*index+2]!=Nil)
		postTraverse(T,2*index+2);
	visitFunc(T[index]);
}

//后序遍历，对每个结点调用函数visit一次且仅一次。
int postOrderTraverse(sqBiTree T,int(*visit)(elemType)){
	visitFunc = visit;
	//树不空
	if(!biTreeEmpty(T)) postTraverse(T,0);
	printf("\n\n");
	return 1;
}

//层序遍历二叉树
void levelOrderTraverse(sqBiTree T,int(*pFunc)(elemType)){
	int i=Max_tree_size-1,j;
	//找到最后一个非空结点的序号
	while(T[i]==Nil)	i--;
	//从根结点起，按层序遍历二叉树
	for(j=0;j<=i;j++){
		//只遍历非空的结点
		if(T[j]!=Nil) (*pFunc)(T[j]);
	}
	printf("\n\n");
}

//逐层、按本层序号输出二叉树
void print(sqBiTree T){
	int j,k;
	position p;
	elemType e;
	for(j=1;j<=biTreeDepth(T);j++){
		printf("The %d layer:",j);
		for(k=1;k<=pow(2,j-1);k++){//pow(2,j-1)为该层的最大结点数
			p.level = j;
			p.order = k;
			e = value(T,p);
			if(e!=Nil)
				printf("%d:'%c' ",k,e);
		}
		printf("\n");
	}
}

int visit(elemType e){
	printf("'%c' ",e);
	return 0;
}


void main(){
	int i,j;
	position p;
	elemType e;
	sqBiTree T,s;
	initBiTree(T);//二叉树的初始化
	
	createBiTree(T);//创建二叉树T=abcdefgh
	//判断数是否为空，求树的深度
	printf("\nBuild a Binary Tree!\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
	
	//寻找根结点
	i = root(T,&e);
	if(i)
		printf("\nThe root of the Binary Tree is:'%c'\n",e);
	else
		printf("\nThe Binary Tres has no root\n");
	
	//层序遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	levelOrderTraverse(T,visit);
	
	//先序遍历
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visit);
	//中序遍历
	printf("inOrder Traverse the Binary Tree:\n");
	inOrderTraverse(T,visit);
	//后序遍历
	printf("postOrder Traverse the Binary Tree:\n");
	postOrderTraverse(T,visit);
	
	//修改结点
	printf("Please enter the modifying node layer and numberical order:\n");
	p.level = 3;p.order = 2;//第level层的第order个结点，注意level和order都是从1开始编号的
	//scanf("%d%d",&p.level,&p.order);
	//获得对应结点的值
	e = value(T,p);
	printf("Know the previous vaule is:'%c'\nEnter the new vlaue:\n",e);
	e = 'i';//新结点的值
	//scanf("%c",&e);
	assign(T,p,e);
	//先序遍历
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visit);
	
	//寻找左右结点和左右兄弟
	printf("The parent of new inserted node '%c' is :'%c'\n", e, parent(T,e));
	printf("The left and right sibling of node '%c' is '%c' and '%c':\n",e, leftSibling(T,e), rightSibling(T,e));
	e = 'c';
	printf("The left and right child of node '%c' is '%c' and '%c':\n", e, leftChild(T,e), rightChild(T,e));
	
	//初始化需要插入的树
	initBiTree(s);//s=jk l//这里有空格
	printf("\nBuild the Binary Tree s which has no right child:\n");
	createBiTree(s);
	//层序遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	levelOrderTraverse(s,visit);
	
	//树s插到树T中，请输入树T中树s的双亲结点 s为左(0)或右(1)子树:
	printf("Insert the Tree s to the Tree T,enter the parent of the Tree s in the Tree T,left Tree(0) and right Tree(1):\n");
	e = 'i';j = 0;//将子树s作为结点'i'的左子树
	//scanf("%c%d",&e,&j);
	insertChild(T,e,j,s);
	print(T);
	
	// 删除子树,请输入待删除子树根结点的层号及对应的本层序号 左(0)或右(1)子树
	printf("\nDelete the Tree T,enter the root of the deleting Child Tree in the Tree T's layer numberical order, left Tree(0) and right Tree(1):\n");
	//: 2 1 0
	p.level = 2;p.order = 1;j = 0;//表示左子树
	//scanf("%d%d%c",&p.level,&p.order,&j);
	deleteChild(T,p,j);
	print(T);
	
	//清空子树
	clearBiTree(T);
	printf("\nEmpty the Binary Tree?%d(1:yes 0:no)\nThe tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
	i = root(T,&e);//寻找根结点
	if(i)
		printf("The root of the Binary Tree is:'%c'\n",e);
	else
		printf("The empty Binary Tres has no root\n");
}
