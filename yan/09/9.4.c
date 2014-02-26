/*
	数据结构C语言版 二叉排序树
	P227
	日期：2012年7月29日
*/
#include <stdio.h>
#include <stdlib.h>

#define N 10 //数据元素个数

typedef int keyType;//设关键字域为整型

typedef struct{
	keyType key;
	int others;
}elemType;//数据元素类型

typedef elemType TElemType;

//二叉树的二叉链表存储表示
typedef struct biTNode{
	TElemType data;//数据域
	struct biTNode *lchild,*rchild;//左右孩子指针
}biTNode,*biTree;

//构造一个空的动态查找表DT
int initDSTable(biTree *DT){
	*DT = NULL;
	return 1;
}

//销毁动态查找表DT
void destroyDSTable(biTree *DT){
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
biTree searchBST(biTree T,keyType key){
	if((!T)||(key==T->data.key)){
		return T;//查找结束
	}else if(key<T->data.key){//在左子树中继续查找
		return searchBST(T->lchild,key);
	}else{//在右子树中继续查找
		return searchBST(T->rchild,key);
	}
}

// 算法9.5(b) P228
// 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，若查找成功，则指针p
// 指向该数据元素结点，并返回1，否则指针p指向查找路径上
// 访问的最后一个结点并返回0，指针f指向T的双亲，其初始调用值为NULL
void searchBSTParent(biTree *T,keyType key,biTree f,biTree *p,int *flag){
	if(!*T){//查找不成功
		*p = f;//f指向T的双亲
		*flag = 0;
	}else if(key==(*T)->data.key){//查找成功
		*p = *T;//指针p指向该数据元素结点
		*flag = 1;
	}else if(key<(*T)->data.key){
		searchBSTParent(&(*T)->lchild,key,*T,p,flag);//在左子树中继续查找
	}else 
		searchBSTParent(&(*T)->rchild,key,*T,p,flag);//在右子树中继续查找
}

// 算法9.6 P228
// 当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回1，
// 否则返回0
int insertBST(biTree *T,elemType e){
	biTree p,s;
	int flag;
	searchBSTParent(T,e.key,NULL,&p,&flag);
	if(!flag){//查找不成功
		s = (biTree)malloc(sizeof(biTNode));
		s->data = e;
		s->lchild = s->rchild = NULL;
		if(!p){
			*T = s;//被插结点*s为新的根结点
		}else if(e.key < p->data.key){
			p->lchild = s;//被插结点*s为左孩子，值小的在左边
		}else{
			p->rchild = s;//被插结点*s为右孩子，值大的在右边
		}
		return 1;
	}else return 0;//树中已有关键字相同的结点，不再插入
}

// 算法9.8 P231
// 从二叉排序树中删除结点p，并重接它的左或右子树
void delete(biTree *p){//注意p是指向指针的指针，能改变指向指针的值即指针地址，参数传递时是传地址。
	biTree q,s;
	// 右子树空则只需重接它的左子树(待删结点是叶子也走此分支)
	if(!(*p)->rchild){//右子树空，只需重接它的左子树
		q = *p;//待删除结点赋给q
		*p = (*p)->lchild;//这里p是指向树结点的指针的指针，它能改变指向指针的值
		free(q);
	}else if(!(*p)->lchild){// 左子树空，只需重接它的右子树
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}else{//左右子树均不空
		/*
		P230方法二：
		*/
		q = *p;
		s = (*p)->lchild;
		while(s->rchild){//转左，然后向右到尽头(找到中序遍历时待删结点的前驱)
			q = s;
			s = s->rchild;
		}
		//s指向被删结点的"前驱"(将被删结点前驱的值取代被删结点的值)
		(*p)->data = s->data;
		if(q!=*p) q->rchild = s->lchild;//重接*q的右子树
		else q->lchild = s->lchild;//重接*q的左子树
		free(s);
	}
}

// 算法9.7 P230
// 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点，并返回1；否则返回0
int deleteBST(biTree *T,keyType key){
	//不存在关键字等于key的数据元素
	if(!*T) return 0;
	else{
		//找到关键字等于key的数据元素
		if(key==(*T)->data.key) delete(T);
		else if(key<(*T)->data.key) deleteBST(&(*T)->lchild,key);
		else deleteBST(&(*T)->rchild,key);
		return 1;
	}
}

// 按关键字的顺序对DT的每个结点调用函数visit()一次
void traverseDSTable(biTree DT,void(*visit)(elemType)){
	if(DT){
		// 像这样中序遍历，最后结果是个非递减顺序
		traverseDSTable(DT->lchild,visit);//先中序遍历左子树
		visit(DT->data);//再访问根结点
		traverseDSTable(DT->rchild,visit);//最后中序遍历右子树
	}
}

void print(elemType c){
	printf("(%d,%d)",c.key,c.others);
}

void main(){
	biTree dt,p;
	int i;
	keyType j;
	
	elemType r[N] = {{45,1},{12,2},{53,3},{3,4},{37,5},
		{24,6},{100,7},{61,8},{90,9},{78,10}};// 以教科书P227图9.7(a)为例 
	initDSTable(&dt);//构造空表
	
	for(i=0;i<N;i++) insertBST(&dt,r[i]);//依次插入数据元素
	
	//遍历排序树
	traverseDSTable(dt,print);
	
	printf("\n\nPlease enter the value for search:\n");
	scanf("%d",&j);
	p = searchBST(dt,j);
	if(p){//找到了值
		printf("\nThe value is in the table:");
		print(p->data);
		//删除值
		deleteBST(&dt,j);
		printf("\nAfter the table delete this value:\n");
		traverseDSTable(dt,print);
		printf("\n");
	}else{
		printf("The value is not in the table");
	}
	destroyDSTable(&dt);
	traverseDSTable(dt,print);
}







