/*
  数据结构C语言版 线索二叉树
  P132-135
*/
#include<stdio.h>
#include<stdlib.h>

typedef char TElemType;

//二叉树的二叉线索存储表示
typedef enum{
	Link,
	Thread
}PointerTag;//Link(0):指针,Thread(1):线索

typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild,*rchild;//左右孩子指针
	PointerTag LTag,RTag;//左右标志
}BiThrNode,*BiThrTreeLink;

TElemType Nil = ' ';//字符型以空格符为空
BiThrTreeLink pre = NULL;//全局变量，始终指向刚刚访问过的结点

//按先序次序输入二叉树中结点的值，构造二叉线索树T
void createBiThrTree(BiThrTreeLink *T){
	TElemType h;
	scanf("%c",&h);
	if(h==Nil){//空
		*T = NULL;
	}else{
		*T = (BiThrTreeLink)malloc(sizeof(BiThrNode));
		if(!*T){
			exit(0);
		}
		(*T)->data = h;//生成根结点
		createBiThrTree(&(*T)->lchild);//递归构造左子树
		//有左孩子
		if((*T)->lchild) (*T)->LTag = Link;
		createBiThrTree(&(*T)->rchild);//递归构造右子树
		//有右孩子
		if((*T)->rchild) (*T)->RTag = Link;
	}
}

// 算法6.5  P134 注意：该函数必须在二叉树线索化或才能调用
// 中序遍历二叉线索树T(头结点)的非递归算法。T不存储任何值
int inOrderTraverse_Thr(BiThrTreeLink T,int(*visit)(TElemType)){
	BiThrTreeLink p;
	p = T->lchild;//p指向根结点
	while(p!=T){//空树或遍历结束时，p==T
		while(p->LTag == Link) p = p->lchild;
		//访问其左子树为空的结点
		if(!visit(p->data)) return 0;
		while(p->RTag == Thread&&p->rchild!=T){
			p = p->rchild;
			(*visit)(p->data);//访问后继结点
		}
		p = p->rchild;
	}
	return 1;
}

// 算法6.7 P135 中序遍历进行中序线索化，
// 将二叉链表中的空指针改为指向前驱或后继的线索
// 即修改空指针的过程
void inThreading(BiThrTreeLink p){
	if(p){
		inThreading(p->lchild);//递归左子树线索化
		if(!p->lchild){//没有左孩子
			p->LTag = Thread;//前驱线索
			p->lchild = pre;//左孩子指针指向前驱
		}
		if(!pre->rchild){//前驱没有右孩子
			pre->RTag = Thread;//后继线索
			pre->rchild = p;//前驱右孩子指针指向后继(当前结点p)
		}
		pre = p;//保持pre指向p的前驱
		inThreading(p->rchild);//递归右子树线索化
	}
}

//算法6.6 P134
//中序遍历二叉树T，并将其中序线索化，Thrt指向头结点。
int inOrderThreading(BiThrTreeLink *Thrt,BiThrTreeLink T){
	*Thrt = (BiThrTreeLink)malloc(sizeof(BiThrNode));//建头结点
	if(!*Thrt) exit(0);
	(*Thrt)->LTag = Link;//标志左孩子为指针
	(*Thrt)->RTag = Thread;//标志右孩子为线索
	(*Thrt)->rchild = *Thrt;//右指针回指
	if(!T){//若二叉树为空，则左指针回指
		(*Thrt)->lchild = *Thrt;
	}else{
		(*Thrt)->lchild = T;//头结点左指针指向树的根
		pre = *Thrt;//默认上一个结点指向头结点
		inThreading(T);//中序遍历进行中序线索化
		pre->rchild = *Thrt;
		pre->RTag = Thread;//最后一个结点线索化
		(*Thrt)->rchild = pre;
	}
	return 1;
}

//先序遍历
void preOrderTraverse(BiThrTreeLink *T,int (*visit)(TElemType)){
	if(!*T) return;
	(*visit)((*T)->data);//先访问根结点
	if((*T)->LTag == Link) preOrderTraverse(&((*T)->lchild),visit);
	if((*T)->RTag == Link) preOrderTraverse(&((*T)->rchild),visit);
}

int vi(TElemType c){
	printf("'%c' ",c);
	return 1;
}

void main(){
	BiThrTreeLink H,T;
	printf("\nBuild a Binary Tree!like abd@@@ce@@f@@,@stand for space\n");
	createBiThrTree(&T);//按先序产生二叉树
	
	printf("\npreOrder traverse non-threading tree:\n");
	preOrderTraverse(&T,vi);//先序遍历二叉树(非线索化遍历)
	
	inOrderThreading(&H,T);//中序遍历，并中序线索化二叉树
	
	printf("\ninOrder traverse threading tree:\n");
	inOrderTraverse_Thr(H,vi);//中序遍历(输出)二叉线索树
	printf("\n");
}





