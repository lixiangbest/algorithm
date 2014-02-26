/*
	数据结构C语言版 平衡二叉树
	P236
	日期：2012年7月30日
*/
#include <stdio.h>
#include <stdlib.h>

#define LH +1 //左高，+1和1是相等的
#define EH 0 //等高
#define RH -1 //右高
#define N 6 //数据元素个数

typedef int keyType;//设关键字域为整型

typedef struct{
	keyType key;
	int order;
}elemType;//数据元素类型


//平衡二叉树的二叉链表存储表示
typedef struct BSTNode{
	elemType data;//数据域
	int bf;//bf结点的平衡因子，只能够取0,-1,1，它是左子树的深度减去右子树的深度得到的
	struct BSTNode *lchild,*rchild;//左右孩子指针
}BSTNode,*BSTree;

//函数定义
// 构造一个空的动态查找表DT
int initDSTable(BSTree *DT);
//销毁动态查找表DT
void destroyDSTable(BSTree *DT);
//平衡二叉树的查找
BSTree searchBST(BSTree T,keyType key);
//对二叉排序树进行右旋转处理
void R_Rotate(BSTree *p);
//对二叉排序树进行左旋转处理
void L_Rotate(BSTree *p);
//对以指针T所指结点为根的二叉树作左平衡旋转处理，本算法结束时，指针T指向新的根结点。
void leftBalance(BSTree *T);
// 对以指针T所指结点为根的二叉树作右平衡旋转处理，本算法结束时，指针T指向新的根结点
void rightBalance(BSTree *T);
//若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素为e的新结点，
//并返回1，否则返回0。若因插入而使二叉排序树失去平衡，则作平衡旋转处理，
//布尔变量taller反映T长高与否
int insertAVL(BSTree *T,elemType e,int *taller);
//中序遍历二叉排序树
void traverseDSTable(BSTree DT,void(*visit)(BSTree));
void print(BSTree DT);

// 构造一个空的动态查找表DT
int initDSTable(BSTree *DT){
	*DT = NULL;
	return 1;
}

//销毁动态查找表DT
void destroyDSTable(BSTree *DT){
	if(*DT){//非空树
		if((*DT)->lchild) destroyDSTable(&(*DT)->lchild);//销毁左孩子子树
		if((*DT)->rchild) destroyDSTable(&(*DT)->rchild);//销毁左孩子子树
		free(*DT);//释放根结点
		*DT = NULL;//空指针赋0
	}
}

// 算法9.5(a) P228
// 在根结点T所指二叉排序树中递归地查找某关键字等于key的数据元素
// 若查找成功，则返回指向该数据元素结点的指针，否则返回空指针
BSTree searchBST(BSTree T,keyType key){
	if((!T)||(key==T->data.key)){
		return T;//查找结束
	}else if(key<T->data.key){//在左子树中继续查找
		return searchBST(T->lchild,key);
	}else{//在右子树中继续查找
		return searchBST(T->rchild,key);
	}
	return NULL;
}

// 算法9.9 P236
// 对以*p为根的二叉排序树作右旋顺时针处理，处理之后p指向新的树根结点，
// 即旋转处理之前的左子树的根结点
void R_Rotate(BSTree *p){
	BSTree lc;
	lc = (*p)->lchild;//lc指向p的左子树根结点
	(*p)->lchild = lc->rchild;//lc的右子树挂接在p的左子树
	lc->rchild = *p;
	*p = lc;//p指向新的根结点
}

// 算法9.10 P236
// 对以*p为根的二叉排序树作左旋逆时针处理，处理之后p指向新的树根结点，即旋转处理之前的右子树的根结点。
void L_Rotate(BSTree *p){
	BSTree rc;
	rc = (*p)->rchild;//rc指向p的右子树根结点
	(*p)->rchild = rc->lchild;//rc的左子树挂接为p的右子树
	rc->lchild = *p;
	*p = rc;//p指向新的根结点
}

// 算法9.12 P238
// 对以指针T所指结点为根的二叉树作左平衡处理，本算法结束时，指针T指向新的根结点。
void leftBalance(BSTree *T){
	BSTree lc,rd;
	lc = (*T)->lchild;//lc指向*T的左子树根结点
	switch(lc->bf){//检查*T的左子树的平衡度，并作相应平衡处理
		case LH://新结点插入在*T的左孩子的左子树上，要作单右旋处理
			(*T)->bf = lc->bf = EH;
			R_Rotate(T);
			break;
		case RH://新结点插入在*T的左孩子的右子树上，要做双旋处理
			rd = lc->rchild;//rd指向*T的左孩子的右子树根
			switch(rd->bf){//修改*T及其左孩子的平衡因子
				case LH:
					(*T)->bf = RH;
					lc->bf = EH;
					break;
				case EH:
					(*T)->bf = lc->bf = EH;
					break;
				case RH:
					(*T)->bf = EH;
					lc->bf = LH;
			}
			rd->bf = EH;
			L_Rotate(&(*T)->lchild);//对*T的左子树作左旋平衡处理
			R_Rotate(T);//对*T作右旋平衡处理
	}
}

// 对以指针T所指结点为根的二叉树作右平衡处理，本算法结束时，指针T指向新的根结点
void rightBalance(BSTree *T){
	BSTree rc,rd;
	rc = (*T)->rchild;//rc指向*T的右子树根结点
	switch(rc->bf){//检查*T的右子树的平衡度，并作相应平衡处理
		case RH://新结点插入在*T的右孩子的右子树上，要作单左旋处理
			(*T)->bf = rc->bf = EH;
			L_Rotate(T);//作左逆时针
			break;
		case LH://新结点插入在*T的右孩子的左子树上，要做双旋处理
			rd = rc->lchild;//rd指向*T的右孩子的左子树根
			switch(rd->bf){//修改*T及其右孩子的平衡因子
				case RH:
					(*T)->bf = LH;
					rc->bf = EH;
					break;
				case EH:
					(*T)->bf = rc->bf = EH;
					break;
				case LH:
					(*T)->bf = EH;
					rc->bf = RH;
			}
			rd->bf = EH;
			R_Rotate(&(*T)->rchild);//对*T的右子树作右旋处理
			//traverseDSTable(*T,print);
			L_Rotate(T);//对*T作左旋处理
	}
}

// 算法9.11
// 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素为e的新结点，
// 并返回1，否则返回0。若因插入而使二叉排序树失去平衡，则作平衡旋转处理，
// 布尔变量taller反映T长高与否
int insertAVL(BSTree *T,elemType e,int *taller){
	if(!*T){//根结点为空，插入新结点，树“长高”，置taller为1
		*T = (BSTree)malloc(sizeof(BSTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;//0
		*taller = 1;
		printf("Insert node:%d %d\n",e.key,(*T)->bf);
	}else{
		printf("Root node:%d,%d\n",(*T)->data.key,(*T)->bf);//输出根结点
		if(e.key==(*T)->data.key){//树根结点和e有相同关键字，该结点则不再插入
			*taller = 0;
			return 0;//插入不成功，返回0
		}
		if(e.key<(*T)->data.key){//待插入结点小于根结点，则应继续在*T的左子树中进行搜索
			//未插入，插入不成功
			if(!insertAVL(&(*T)->lchild,e,taller)) return 0;
			if(*taller){//已插入到*T的左子树中且左子树“长高”
				printf("before left:%d %d\n",(*T)->data.key,(*T)->bf);
				switch((*T)->bf){//检查*T的平衡度
					case LH://原本左子树比右子树高，需要作左平衡处理
						leftBalance(T);
						*taller = 0;//标志没长高
						break;
					case EH://原本左、右子树等高，现因左子树增高而使树增高
						(*T)->bf = LH;
						*taller = 1;//标志长高
						break;
					case RH://原本右子树比左子树高，现左、右子树等高
						(*T)->bf = EH;
						*taller = 0;//标志没长高
						break;
				}
				printf("after left:%d %d\n",(*T)->data.key,(*T)->bf);
			}
		}else{//待插入结点大于根结点，应继续在*T的右子树中进行搜索
			//未插入，插入不成功
			if(!insertAVL(&(*T)->rchild,e,taller)) return 0;
			if(*taller){//已插入到*T的右子树中且右子树“长高”
				printf("before right:%d %d\n",(*T)->data.key,(*T)->bf);
				switch((*T)->bf){//检查*T的平衡度
					case LH://原本左子树比右子树高，现左、右子树等高
						(*T)->bf = EH;
						*taller = 0;//标志没长高
						break;
					case EH://原本左、右子树等高，现因右子树增高而使树增高
						(*T)->bf = RH;
						*taller = 1;//标志长高
						break;
					case RH://原本右子树比左子树高，需要作右平衡处理
						traverseDSTable(*T,print);
						printf("before balance: %d %d\n",(*T)->data.key,(*T)->bf);;
						rightBalance(T);//T是指向指针的指针
						*taller = 0;//标志没长高
						break;
				}
				printf("after right:%d %d\n",(*T)->data.key,(*T)->bf);
			}
		}
	}
	return 1;//插入成功
}

// 按关键字的顺序对DT的每个结点调用函数visit()一次
void traverseDSTable(BSTree DT,void(*visit)(BSTree)){
	if(DT){
		visit(DT);//再访问根结点
		traverseDSTable(DT->lchild,visit);//先中序遍历左子树 
		traverseDSTable(DT->rchild,visit);//最后中序遍历右子树 
	}else{
		printf("()");//空括号表示子树为空
	}
}

void print(BSTree DT){
	printf("(%d,%d,%d)",DT->data.key,DT->data.order,DT->bf);
}

void main(){
	BSTree dt,p;
	int k;//代表taller值
	int back;//insertAVL函数返回值
	int i;
	keyType j;
	elemType r[N] = {{13,1},{24,2},{37,3},{90,4},{53,5},{9,6}};//以教科书P234图9.12为例
	
	initDSTable(&dt);//初始化空树
	for(i=0;i<N;i++){
		printf("\ni=%d\n",i);
		back = insertAVL(&dt,r[i],&k);//建平衡二叉树，dt和k都是传地址
		//if(i==4){printf("%d\n",k);traverseDSTable(dt,print);exit(0);}
	}
	printf("Middle order traverse the Balance Binary Tree:\n");
	traverseDSTable(dt,print);//按关键字顺序遍历二叉树
	printf("\nPlease enter the key word for search:\n");
	//scanf("%d",&j);
	j = 13;
	p = searchBST(dt,j);//查找给定关键字的记录
	if(p){
		print(p);
	}else printf("Not found!");
	printf("\n");
	destroyDSTable(&dt);
}

