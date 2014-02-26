/*
  数据结构C语言版 二叉树的三叉链表存储表示
  P127
*/
#include<stdio.h>
#include<stdlib.h>

typedef char TElemType;

//二叉树的三叉链表存储表示
typedef struct BiPTNode{
	TElemType data;
	struct BiPTNode *parent,*lchild,*rchild;//双亲、左右孩子指针
}BiPTNode,*BiPTreeLink;

typedef BiPTreeLink QElemType;//设队列元素为二叉树的指针类型

typedef struct QNode{
	QElemType data;//数据域
	struct QNode *next;//指针域
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,//队头指针，指针域指向队头元素
			 rear;//队尾指针，指向队尾元素
}LinkQueue;

TElemType Nil = ' ';//字符型以空格符为空

// 构造空二叉树T
int initBiPTree(BiPTreeLink *T){
	*T = NULL;
	return 1;
}

//销毁二叉树T
//注意：BiTreeLink本身就是指针
void destroyBiPTree(BiPTreeLink *T){
	if(*T){//非空树
		//左孩子
		if((*T)->lchild)
			//销毁左孩子子树
			destroyBiPTree(&(*T)->lchild);
		//右孩子
		if((*T)->rchild)
			//销毁右孩子子树
			destroyBiPTree(&(*T)->rchild);
		free(*T);//释放根结点
		*T = NULL;//空指针赋值0
	}
}

#define clearBiPTree destroyBiPTree

//按先序次序输入二叉树中结点的值(可为字符型或整型，在主程序中定义)
//构造仅缺双亲指针的三叉链表表示的二叉树T。变量Nil表示空(子)树
void create(BiPTreeLink *T){
	TElemType ch;
	//%*c吃掉回车符（重要）
	//scanf("%c%*c",&ch);
	scanf("%c",&ch);
	if(ch==Nil){//空
		*T = NULL;
	}else{
		*T = (BiPTreeLink)malloc(sizeof(BiPTNode));
		if(!*T){
			exit(0);
		}
		(*T)->data = ch;//生成根结点
		create(&(*T)->lchild);//构造左子树
		create(&(*T)->rchild);//构造右子树
	}
}

//构造一个空队列Q
int initQueue(LinkQueue *Q){//LinkQueue不是指针
	//动态分配一个空间
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(0);
	//队头指针指向空，无数据域，这样构成了一个空队列
	Q->front->next = NULL;
	return 1;
}

//插入元素e为Q的新的队尾元素
int enQueue(LinkQueue *Q,QElemType e){
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	//存储分配失败
	if(!p) exit(0);
	//生成一个以e为数据域的队列元素
	p->data = e;
	p->next = NULL;
	//将该新队列元素接在队尾的后面
	Q->rear->next = p;
	Q->rear = p;
	return 1;
}

//若队列不空，删除Q的队头元素，用e返回其值，并返回1，否则返回0
int deQueue(LinkQueue *Q,QElemType *e){
	QueuePtr p;
	//队头和队尾相等
	if(Q->front==Q->rear) return 0;
	p = Q->front->next;//队头元素
	*e = p->data;
	Q->front->next = p->next;
	//说明队列空
	if(Q->rear == p)	Q->rear = Q->front;
	free(p);
	return 1;
}

//若Q为空队列，则返回1，否则返回0
int queueEmpty(LinkQueue Q){//传值而不是传地址
	if(Q.front == Q.rear)	return 1;
	else return 0;
}

// 按先序次序输入二叉树中结点的值（可为字符型或整型，在主程中定义）， 
// 构造三叉链表表示的二叉树T 
int createBiPTree(BiPTreeLink *T){
	LinkQueue q;
	QElemType a;
	create(T);//构造二叉树（缺双亲指针）
	if(*T){//非空树
		(*T)->parent = NULL;//根结点的双亲为“空”
		initQueue(&q);//初始化队列
		enQueue(&q,*T);//根指针入队
		while(!queueEmpty(q)){//队不空
			deQueue(&q,&a);//出队，队列元素赋给a
			if(a->lchild){//左孩子
				a->lchild->parent = a;//给左孩子的双亲指针赋值
				enQueue(&q,a->lchild);//左孩子入队
			}
			if(a->rchild){//右孩子
				a->rchild->parent = a;//给右孩子的双亲指针赋值
				enQueue(&q,a->rchild);//右孩子入队
			}
		}
	}
	return 1;
}

//若T为空二叉树，则返回1，否则0
int biPTreeEmpty(BiPTreeLink T){
	if(T) return 0;
	else return 1;
}

//返回T的深度
int biPTreeDepth(BiPTreeLink T){
	int i,j;
	//树空
	if(!T) return 0;
	//左子树
	if(T->lchild)	i = biPTreeDepth(T->lchild);//递归求深度
	else i = 0;
	//右子树
	if(T->rchild)	j = biPTreeDepth(T->rchild);
	else j = 0;
	return i>j?i+1:j+1;
}

//返回T的根
TElemType root(BiPTreeLink T){
	if(T) return T->data;
	else return Nil;
}

//返回p所指结点的值
TElemType value(BiPTreeLink p){
	return p->data;
}

//给p所指结点赋值为value
void assign(BiPTreeLink p,TElemType value){
	p->data = value;
}

//返回二叉树T中指向元素值为e的结点的指针
BiPTreeLink point(BiPTreeLink T,TElemType e){
	LinkQueue q;
	QElemType a;
	if(T){//非空树
		initQueue(&q);//初始化队列
		enQueue(&q,T);//根结点入队
		while(!queueEmpty(q)){//队列不空
			deQueue(&q,&a);//出队，队列元素赋给a
			if(a->data==e) return a;
			//有左孩子
			if(a->lchild) enQueue(&q,a->lchild);//入队左孩子
			//有右孩子
			if(a->rchild) enQueue(&q,a->rchild);//入队右孩子
		}
	}
	return NULL;
}

//若e是T的非根结点，则返回它的双亲，否则返回“空”
TElemType parent(BiPTreeLink T,TElemType e){
	BiPTreeLink a;
	if(T){//非空树
		a = point(T,e);//a是结点e的指针
		//T中存在结点e且e是非根结点
		if(a&&a!=T)
			return a->parent->data;//返回e的双亲的值
	}
	return Nil;//其余情况返回空
}

//返回e的左孩子，若e无左孩子，则返回“空”
TElemType leftChild(BiPTreeLink T,TElemType e){
	BiPTreeLink a;
	if(T){//非空树
		a = point(T,e);//a是结点e的指针
		//T中存在结点e且e存在左孩子
		if(a&&a->lchild)
			return a->lchild->data;//返回e的左孩子的值
	}
	return Nil;//其余情况返回空
}

//返回e的右孩子，若e无右孩子，则返回“空”
TElemType rightChild(BiPTreeLink T,TElemType e){
	BiPTreeLink a;
	if(T){//非空树
		a = point(T,e);//a是结点e的指针
		//T中存在结点e且e存在右孩子
		if(a&&a->rchild)
			return a->rchild->data;//返回e的右孩子的值
	}
	return Nil;//其余情况返回空
}

//返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂
TElemType leftSibling(BiPTreeLink T,TElemType e){ 
	BiPTreeLink a;
	if(T){//非空树
		a=point(T,e);//a是结点e的指针 
		//T中存在结点e且e存在左兄弟，根结点没有左右兄弟
		if(a&&a!=T&&a->parent->lchild&&a->parent->lchild!=a)
			return a->parent->lchild->data; //返回e的左兄弟的值 
	}
	return Nil; //其余情况返回空 
}

//返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂
TElemType rightSibling(BiPTreeLink T,TElemType e){ 
	BiPTreeLink a;
	if(T){//非空树
		a=point(T,e); //a是结点e的指针 
		//T中存在结点e且e存在右兄弟
		if(a&&a!=T&&a->parent->rchild&&a->parent->rchild!=a) 
			return a->parent->rchild->data; //返回e的右兄弟的值 
	}
	return Nil;//其余情况返回空 
}

//根据LR为0或1，插入c为T中p所指结点的左或右子树。
//p所指结点的原有左或右子树则成为c的右子树
int insertChild(BiPTreeLink p,int LR,BiPTreeLink c){
	if(p){//p不空
		if(LR==0){
			c->rchild = p->lchild;
			//c有右孩子(p原有左孩子)
			if(c->rchild) c->rchild->parent = c;
			p->lchild = c;
			c->parent = p;
		}else{//LR==1
			c->rchild = p->rchild;
			if(c->rchild) c->rchild->parent = c;
			p->rchild = c;
			c->parent = p;
		}
		return 1;
	}
	return 0;
}

//根据LR为0或1，删除T中所指结点的左或右子树
int deleteChild(BiPTreeLink p,int LR){
	if(p){//p不空
		//删除左子树
		if(LR==0)	clearBiPTree(&p->lchild);
		else	clearBiPTree(&p->rchild);
		return 1;
	}
	return 0;//p空
}

//先序递归遍历T，对每个结点调用函数visit一次且仅一次
void preOrderTraverse(BiPTreeLink T,int(*visit)(BiPTreeLink)){
	//T不空
	if(T){
		//先访问根结点
		(*visit)(T);//visit指向函数的入口地址
		preOrderTraverse(T->lchild,visit);//再先序遍历左子树
		preOrderTraverse(T->rchild,visit);//最后先序遍历右子树
	}
}

//中序递归遍历T，对每个结点调用函数visit一次且仅一次
void inOrderTraverse(BiPTreeLink T,int(*visit)(BiPTreeLink)){
	//T不空
	if(T){
		inOrderTraverse(T->lchild,visit);//中序遍历左子树
		//再访问根结点
		(*visit)(T);//visit指向函数的入口地址
		inOrderTraverse(T->rchild,visit);//最后中序遍历右子树
	}
}

// 后序递归遍历T，对每个结点调用函数visit一次且仅一次
void postOrderTraverse(BiPTreeLink T,int(*visit)(BiPTreeLink)){
	//T不空
	if(T){
		postOrderTraverse(T->lchild,visit);//先后序遍历左子树
		postOrderTraverse(T->rchild,visit);//再后序遍历右子树
		//最后访问根结点
		(*visit)(T);//visit指向函数的入口地址
	}
}

// 层序递归遍历T(利用队列)，对每个结点调用函数visit一次且仅一次
void levelOrderTraverse(BiPTreeLink T,int(*visit)(BiPTreeLink)){
	LinkQueue q;
	QElemType a;
	if(T){
		initQueue(&q);
		enQueue(&q,T);//队列不空
		while(!queueEmpty(q)){
			deQueue(&q,&a);//出队列
			(*visit)(a);//访问元素
			if(a->lchild!=NULL)	enQueue(&q,a->lchild);
			if(a->rchild!=NULL) enQueue(&q,a->rchild);
		}
	}
}

//结点元素的输出
int visit(BiPTreeLink T){
	//非空
	if(T)	printf("'%c' ",T->data);
	return 1;
}

//访问结点
int visitT(BiPTreeLink T){
	//非空
	if(T)	printf("'%c' is ",T->data);
	if(T->parent){//T有双亲
		printf("'%c' ",T->parent->data);
		if(T->parent->lchild==T)
			printf("left child!\n");
		else
			printf("right child\n");
	}else
		printf("root\n");
	return 1;
}

void main(){
	int i;
	BiPTreeLink T,c,q,p;
	TElemType e1,e2;
	initBiPTree(&T);
	//判断数是否为空，求树的深度
	printf("\nInit a Binary Tree!\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biPTreeEmpty(T),biPTreeDepth(T));
	//寻找根结点
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
	
	//请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)
	printf("\nBuild a Binary Tree!like abc@@d@@efg@@h@@@,@stand for space\n");
	createBiPTree(&T);
	//判断数是否为空，求树的深度
	printf("\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biPTreeEmpty(T),biPTreeDepth(T));
	//寻找根结点
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
	
	//层序递归遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	levelOrderTraverse(T,visitT);
	
	//先序遍历
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//中序递归遍历
	printf("\n\ninOrder recursion Traverse the Binary Tree:\n");
	inOrderTraverse(T,visitT);
	
	//后序递归遍历
	printf("\npostOrder recursion Traverse the Binary Tree:\n");
	postOrderTraverse(T,visitT);
	
	//修改结点
	e1 = 'b';//原值
	//scanf("%c",&e1);
	c = point(T,e1);//获得e1对应的指针
	//获得对应结点的值
	printf("\n\nKnow the previous vaule is:'%c'\nEnter the new vlaue:\n",value(c));
	e2 = 'r';//新结点的值
	//scanf("%c",&e2);
	assign(c,e2);//赋新值
	//先序遍历
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//寻找双亲
	e1 = parent(T,e2);
	if(e1!=Nil) printf("\nthe parent of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no parent\n",e2);
	
	//寻找左孩子
	e1 = leftChild(T,e2);
	if(e1!=Nil) printf("\nthe left child of '%c' is : '%c'\n",e2,e1);
	else printf("\n'%c' has no left child\n",e2);
	
	//寻找右孩子
	e1 = rightChild(T,e2);
	if(e1!=Nil) printf("\nthe right child of '%c' is : '%c'\n",e2,e1);
	else printf("\n'%c' has no right child\n",e2);
	
	//寻找左兄弟
	e1 = leftSibling(T,e2);
	if(e1!=Nil) printf("\nthe left sibling of '%c' is : '%c'\n",e2,e1);
	else printf("\n'%c' has no left sibling\n",e2);
	
	//寻找右兄弟
	e1 = rightSibling(T,e2);
	if(e1!=Nil) printf("\nthe right sibiling of '%c' is : '%c'\n",e2,e1);
	else printf("\n'%c' has no right sibiling\n",e2);
	
	//初始化需要插入的树
	initBiPTree(&c);//s=jk   //这里有三个空格
	printf("\nBuild the Binary Tree c which has no right child:\n");
	c = (BiPTreeLink)malloc(sizeof(BiPTNode));
	p = (BiPTreeLink)malloc(sizeof(BiPTNode));
	c->lchild = p;
	c->rchild = NULL;
	c->parent = NULL;
	c->data = 'm';
	p->lchild = p->rchild = NULL;
	p->parent = c;
	p->data = 'n';
	
	//createBiTree(&c);
	//先序递归遍历
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(c,visitT);
	
	//树s插到树T中，请输入树T中树s的双亲结点 s为左(0)或右(1)子树:
	printf("\n\nInsert the Tree s to the Tree T,enter the parent of the Tree c in the Tree T,left Tree(0) and right Tree(1):\n");
	e1= 'r';i = 0;//将子树c作为结点'r'的左子树
	//scanf("%c%d",&e1,&i);
	p = point(T,e1);//p是T中树c的双亲结点指针
	insertChild(p,i,c);
	//先序递归遍历
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	// 删除子树,请输入待删除子树根结点 左(0)或右(1)子树
	printf("\n\nDelete the Tree s,enter the root of the deleting Child Tree, left Tree(0) and right Tree(1):\n");
	e1= 'r';i = 1;//删除父结点为'r'的右子树
	p = point(T,e1);//p是T中树c的双亲结点指针
	deleteChild(p,i);
	//先序递归遍历
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//清空子树
	clearBiPTree(&T);
	printf("\n\nEmpty the Binary Tree?%d(1:yes 0:no)\nThe tree depth=%d\n",biPTreeEmpty(T),biPTreeDepth(T));
	//寻找根结点
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
}

